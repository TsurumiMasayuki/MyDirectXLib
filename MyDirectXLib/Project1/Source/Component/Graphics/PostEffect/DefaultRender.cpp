#include "DefaultRender.h"

#include <d3d11.h>

#include "Actor\GameObject.h"
#include "Component\Transform.h"

#include "Def\Screen.h"

#include "Device\Camera.h"
#include "Device\Renderer.h"
#include "Device\GameDevice.h"
#include "Device\DirectXManager.h"

#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"

#include "Device\Resource\RenderTarget.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\Shader\VertexShader.h"
#include "Device\Resource\Shader\PixelShader.h"

DefaultRender::DefaultRender(GameObject * pUser, int drawOrder, GraphicsLayer sourceLayer, GraphicsLayer destLayer)
	: AbstractComponent(pUser),
	m_DrawOrder(drawOrder),
	m_SourceLayer(sourceLayer),
	m_DestLayer(destLayer)
{
	auto pRenderer = GameDevice::getRenderer();
	pRenderer->addPostEffect(this);

	m_pSourceRT = pRenderer->getRenderTarget(sourceLayer);

	m_pVertexShader = ShaderManager::GetVertexShader("BasicVS");
	m_pPixelShader = ShaderManager::GetPixelShader("BasicPS");
}

DefaultRender::~DefaultRender()
{
	GameDevice::getRenderer()->removePostEffect(this);

	delete m_pVertices;
	delete m_pIndices;

	m_pInputLayout->Release();
	m_pSampler->Release();
}

void DefaultRender::onStart()
{
	auto pDevice = DirectXManager::getDevice();

	//InputLayout作成
	D3D11_INPUT_ELEMENT_DESC inputDesc[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	m_pVertexShader->createInputLayout(
		pDevice,
		inputDesc,
		2,
		&m_pInputLayout
	);

	//SamplerState作成
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	pDevice->CreateSamplerState(&samplerDesc, &m_pSampler);

	//頂点バッファ作成
	float width = 0.5f;
	float height = 0.5f;

	//四角の頂点情報作成
	BasicVertex vertices[]
	{
		{{ -width,  height, 0.0f }, {0.0f, 0.0f}},
		{{  width, -height, 0.0f }, {1.0f, 1.0f}},
		{{ -width, -height, 0.0f }, {0.0f, 1.0f}},
		{{  width,  height, 0.0f }, {1.0f, 0.0f}},
	};

	m_pVertices = new VertexBuffer();
	m_pVertices->init(pDevice, sizeof(BasicVertex) * 4, vertices);

	//インデックスバッファ作成
	UINT indices[]
	{
		0, 1, 2,
		0, 3, 1
	};

	m_pIndices = new IndexBuffer();
	m_pIndices->init(pDevice, sizeof(UINT) * 6, indices);
}

void DefaultRender::onUpdate()
{
}

void DefaultRender::draw()
{
	if (!isActive()) return;

	auto pDeviceContext = DirectXManager::getDeviceContext();

	//シェーダーを設定
	pDeviceContext->VSSetShader(m_pVertexShader->getShader(), nullptr, 0);
	pDeviceContext->PSSetShader(m_pPixelShader->getShader(), nullptr, 0);

	//画像表示用のInputLayoutとSamplerを設定
	pDeviceContext->IASetInputLayout(m_pInputLayout);
	pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);

	//頂点バッファ設定
	auto vertices = m_pVertices->getBuffer();
	UINT stride = sizeof(BasicVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);

	//インデックスバッファ設定
	pDeviceContext->IASetIndexBuffer(m_pIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//SRVをスロット0に設定
	auto sourceSRV = m_pSourceRT->getSRV();
	pDeviceContext->PSSetShaderResources(0, 1, &sourceSRV);

	//定数バッファの行列用データを作成
	BasicCBuffer wvpCBuffer;
	//計算順がおかしくなってしまうので先にこちらを計算する
	auto world = m_pUser->getTransform()->getWorldMatrix();
	auto wvp = world * Camera::getViewProjMatrix2D();
	DirectX::XMStoreFloat4x4(&wvpCBuffer.wvp, DirectX::XMMatrixTranspose(wvp));

	//定数バッファ作成
	ConstantBuffer vsCBuffer;
	vsCBuffer.init(DirectXManager::getDevice(), sizeof(BasicCBuffer), &wvpCBuffer);

	//頂点シェーダーに定数バッファ設定
	auto vsD3DConstantBuffer = vsCBuffer.getBuffer();
	pDeviceContext->VSSetConstantBuffers(0, 1, &vsD3DConstantBuffer);

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//描画
	pDeviceContext->DrawIndexed(6, 0, 0);

	sourceSRV->Release();
}
