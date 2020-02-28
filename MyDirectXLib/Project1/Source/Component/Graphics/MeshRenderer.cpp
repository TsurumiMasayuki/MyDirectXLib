#include "MeshRenderer.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Actor\GameObject.h"
#include "Component\Transform.h"

#include "Device\Resource\Mesh.h"
#include "Device\Resource\MeshManager.h"
#include "Device\Resource\TextureManager.h"
#include "Device\Resource\Shader\VertexShader.h"
#include "Device\Resource\Shader\PixelShader.h"
#include "Device\Resource\Shader\ShaderManager.h"

#include "Device\Base\MeshVertex.h"

#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"
#include "Device\Buffer\WVPConstantBuffer.h"
#include "Device\Buffer\MeshPSBuffer.h"

#include "Device\DirectXManager.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"
#include "Device\Camera.h"

#include "Utility\Color.h"

using namespace DirectX;

MeshRenderer::MeshRenderer(GameObject * pUser, int drawOrder)
	: AbstractComponent(pUser),
	m_DrawOrder(drawOrder),
	m_pMesh(nullptr),
	m_pColor(new Color(DirectX::Colors::White))
{
	//Rendererに登録
	GameDevice::getRenderer()->addMesh(this);

	m_pVertexShader = ShaderManager::GetVertexShader("MeshVS");
	m_pPixelShader = ShaderManager::GetPixelShader("MeshPS");
}

MeshRenderer::~MeshRenderer()
{
	//Rendererから登録解除
	GameDevice::getRenderer()->removeMesh(this);

	delete m_pColor;
}

void MeshRenderer::onStart()
{
}

void MeshRenderer::onUpdate()
{
}

void MeshRenderer::setMesh(std::string meshName)
{
	m_pMesh = GameDevice::getMeshManager()->getMesh(meshName);
}

int MeshRenderer::getDrawOrder()
{
	return m_DrawOrder;
}

void MeshRenderer::draw()
{
	if (m_pMesh == nullptr) return;
	if (!isActive()) return;

	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//ワールド行列
	XMMATRIX world = XMMatrixTranspose(m_pUser->getTransform()->getWorldMatrix());
	//View * Projの行列
	XMMATRIX viewProj = XMMatrixTranspose(Camera::getViewProjMatrix3D());
	//法線用変換行列
	XMMATRIX worldInv = XMMatrixTranspose(XMMatrixInverse(nullptr, world));

	//頂点シェーダー用定数バッファ作成
	WVPConstantBuffer wvpCBuffer;
	XMStoreFloat4x4(&wvpCBuffer.world, world);
	XMStoreFloat4x4(&wvpCBuffer.viewProj, viewProj);
	XMStoreFloat4x4(&wvpCBuffer.worldInv, worldInv);

	ConstantBuffer vsBuffer;
	vsBuffer.init(pDevice, sizeof(WVPConstantBuffer), &wvpCBuffer);
	auto pVSBuffer = vsBuffer.getBuffer();

	//ピクセルシェーダー用定数バッファ作成
	MeshPSBuffer meshCBuffer;
	XMStoreFloat4(&meshCBuffer.cameraPos, Camera::getPosition().toXMVector());
	XMStoreFloat4(&meshCBuffer.color, m_pColor->toXMVECTOR());
	XMStoreFloat4(&meshCBuffer.lightPos, Vec3(0.0f, 1.0f, 0.0f).toXMVector());
	XMStoreFloat4(&meshCBuffer.lightDir, Vec3(-0.5f, -0.5f, 0.0f).toXMVector());
	//XMStoreFloat4(&meshCBuffer.lightAttenuation, Vec3(0.0f, 0.0f, 0.02f).toXMVector());
	XMStoreFloat4(&meshCBuffer.lightColor, Vec3(1.0f, 1.0f, 1.0f).toXMVector());

	ConstantBuffer psBuffer;
	psBuffer.init(pDevice, sizeof(MeshPSBuffer), &meshCBuffer);
	auto pPSBuffer = psBuffer.getBuffer();

	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	auto pVertexBuffer = m_pMesh->getVertexBuffer().getBuffer();
	pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(m_pMesh->getIndexBuffer().getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->VSSetShader(m_pVertexShader->getShader(), NULL, 0);
	pDeviceContext->PSSetShader(m_pPixelShader->getShader(), NULL, 0);

	pDeviceContext->VSSetConstantBuffers(0, 1, &pVSBuffer);
	pDeviceContext->PSSetConstantBuffers(0, 1, &pPSBuffer);

	auto texture = TextureManager::getTextureView(m_pMesh->getTextureName());
	pDeviceContext->PSSetShaderResources(0, 1, &texture);

	//描画
	pDeviceContext->DrawIndexed(m_pMesh->getVertexCount(), 0, 0);
}

void MeshRenderer::setColor(const Color & color)
{
	m_pColor->r = color.r;
	m_pColor->g = color.g;
	m_pColor->b = color.b;
	m_pColor->a = color.a;
}

const Color & MeshRenderer::getColor() const
{
	return *m_pColor;
}
