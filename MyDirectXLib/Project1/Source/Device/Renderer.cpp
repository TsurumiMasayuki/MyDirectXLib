#include "Renderer.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "Def\Screen.h"

#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\IRenderer2D.h"
#include "Component\Graphics\PostEffect\IPostEffectRenderer.h"

#include "WindowInstance.h"

#include "Device\Camera.h"
#include "Device\DirectXManager.h"

#include "Device\Base\MeshVertex.h"
#include "Device\Buffer\ConstantBuffer.h"
#include "Device\Buffer\SpriteConstantBuffer.h"

#include "Device\Buffer\WVPConstantBuffer.h"
#include "Device\Resource\Shader\VertexShader.h"
#include "Device\Resource\Shader\PixelShader.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\TextureManager.h"
#include "Device\Resource\RenderTarget.h"

#include "Math\MathUtility.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	for (auto layer : m_RTLayers)
	{
		delete layer.second;
	}

	m_RTLayers.clear();

	m_pMeshInputLayout->Release();
	m_pMeshSampler->Release();

	m_pD2DFactory->Release();
	m_pD2DRenderTarget->Release();
}

void Renderer::init()
{
	initBuffers();
	initRenderTargets();

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	FLOAT dpiX;
	FLOAT dpiY;
	m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES rtProp =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX, dpiY
		);

	//�����_�[�^�[�Q�b�g����e�L�X�g�������ݗp�̃e�N�X�`���擾
	IDXGISurface* pBack;
	m_RTLayers.at(GraphicsLayer::Final)->getRenderTexture()->QueryInterface(__uuidof(IDXGISurface), (LPVOID*)&pBack);
	m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBack, rtProp, &m_pD2DRenderTarget);
}

void Renderer::draw()
{
	//�����_�[�^�[�Q�b�g���N���A
	for (auto layer : m_RTLayers)
	{
		layer.second->clearRenderTarget();
	}

	drawMeshes();
	draw2D();
	drawPostEffects();

	//postEffect();
	//postEffect2();

	DirectXManager::presentSwapChain();
}

void Renderer::addRenderer2D(IRenderer2D * pRenderer)
{
	int myDrawOrder = pRenderer->getDrawOrder();

	auto itr = m_Renderer2DList.begin();
	//�������DrawOrder�������Ȃ�܂Ń��[�v
	while (itr != m_Renderer2DList.end())
	{
		if (myDrawOrder < (*itr)->getDrawOrder())
			break;

		++itr;
	}

	m_Renderer2DList.insert(itr, pRenderer);
}

void Renderer::removeRenderer2D(IRenderer2D * pRenderer)
{
	auto itr = std::find(m_Renderer2DList.begin(), m_Renderer2DList.end(), pRenderer);
	m_Renderer2DList.erase(itr);
}

void Renderer::addMesh(MeshRenderer * pMesh)
{
	int myDrawOrder = pMesh->getDrawOrder();

	auto itr = m_Meshes.begin();
	//�������DrawOrder�������Ȃ�܂Ń��[�v
	while (itr != m_Meshes.end())
	{
		if (myDrawOrder < (*itr)->getDrawOrder())
			break;

		++itr;
	}

	m_Meshes.insert(itr, pMesh);
}

void Renderer::removeMesh(MeshRenderer * pMesh)
{
	auto itr = std::find(m_Meshes.begin(), m_Meshes.end(), pMesh);
	m_Meshes.erase(itr);
}

void Renderer::addPostEffect(IPostEffectRenderer * pPostEffect)
{
	m_PostEffects.emplace_back(pPostEffect);
}

void Renderer::removePostEffect(IPostEffectRenderer * pPostEffect)
{
	auto itr = std::find(m_PostEffects.begin(), m_PostEffects.end(), pPostEffect);
	m_PostEffects.erase(itr);
}

void Renderer::initBuffers()
{
auto pDevice = DirectXManager::getDevice();
#pragma region Mesh�p

	//�C���v�b�g���C�A�E�g�̍쐬
	D3D11_INPUT_ELEMENT_DESC layout[3];
	MeshVertex::getInputDesc(layout);
	ShaderManager::GetVertexShader("MeshVS")->createInputLayout(pDevice, layout, 3, &m_pMeshInputLayout);

	//���X�^���C�U�̍쐬
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_FRONT;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = TRUE;

	pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizer);

	//�T���v���[�̍쐬(3D���f���p)
	D3D11_SAMPLER_DESC meshSamDesc;
	ZeroMemory(&meshSamDesc, sizeof(D3D11_SAMPLER_DESC));
	meshSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	meshSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	meshSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	meshSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	meshSamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	pDevice->CreateSamplerState(&meshSamDesc, &m_pMeshSampler);

#pragma endregion
}

void Renderer::initRenderTargets()
{
	auto pSwapChain = DirectXManager::getSwapChain();
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//�r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (float)Screen::getWindowWidth();
	vp.Height = (float)Screen::getWindowHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	pDeviceContext->RSSetViewports(1, &vp);

	//SwapChain����o�b�N�o�b�t�@���擾
	ID3D11Texture2D* pBack;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);
	//��ʕ`��pRTV�쐬
	RenderTarget* pRTFinal = new RenderTarget(pBack);
	pRTFinal->setClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	m_RTLayers.emplace(GraphicsLayer::Final, pRTFinal);

	//�ʏ�`��pRTV�쐬
	RenderTarget* pRTDefault = new RenderTarget(Screen::getWindowWidth(), Screen::getWindowHeight());
	pRTDefault->setClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	m_RTLayers.emplace(GraphicsLayer::Default, pRTDefault);

	//�u���b�N�pRTV�쐬
	RenderTarget* pRTBlock = new RenderTarget(Screen::getWindowWidth(), Screen::getWindowHeight());
	pRTBlock->setClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	m_RTLayers.emplace(GraphicsLayer::Block, pRTBlock);

	//�����Ԃ��pRTV�쐬
	RenderTarget* pRTSplash = new RenderTarget(Screen::getWindowWidth(), Screen::getWindowHeight());
	pRTSplash->setClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	m_RTLayers.emplace(GraphicsLayer::Splash, pRTSplash);

	//���^�{�[���pRTV�쐬
	RenderTarget* pRTMetaBall = new RenderTarget(Screen::getWindowWidth(), Screen::getWindowHeight());
	pRTMetaBall->setClearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	m_RTLayers.emplace(GraphicsLayer::MetaBall, pRTMetaBall);
}

void Renderer::draw2D()
{	//�����̕`��
	m_pD2DRenderTarget->BeginDraw();
	for (auto renderer2D : m_Renderer2DList)
	{
		//�e�`��R���|�[�l���g�̃��C���[�ݒ���擾
		m_RTLayers.at(renderer2D->getGraphicsLayer())->setRenderTarget(false);
		renderer2D->draw();
	}
	m_pD2DRenderTarget->EndDraw();
}

void Renderer::drawMeshes()
{
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//�ʏ�`��p�����_�[�^�[�Q�b�g��[�x�o�b�t�@�t���ŃZ�b�g
	m_RTLayers.at(GraphicsLayer::Default)->setRenderTarget(true);

	pDeviceContext->IASetInputLayout(m_pMeshInputLayout);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->RSSetState(m_pRasterizer);
	pDeviceContext->PSSetSamplers(0, 1, &m_pMeshSampler);

	for (auto mesh : m_Meshes)
	{
		mesh->draw();
	}
}

void Renderer::drawPostEffects()
{
	m_RTLayers.at(GraphicsLayer::Final)->setRenderTarget(false);

	for (auto postEffect : m_PostEffects)
	{
		postEffect->draw();
	}
}

void Renderer::postEffect()
{
	//m_RTLayers.at(GraphicsLayer::Final)->setRenderTarget(true);

	//auto pDeviceContext = DirectXManager::getDeviceContext();
	////�V�F�[�_�[��ݒ�
	//pDeviceContext->VSSetShader(ShaderManager::GetVertexShaderInstance("BasicVS"), nullptr, 0);
	//pDeviceContext->PSSetShader(ShaderManager::GetPixelShaderInstance("MetaBallPS"), nullptr, 0);

	////�摜�\���p��InputLayout��Sampler��ݒ�
	//pDeviceContext->IASetInputLayout(m_pSpriteInputLayout);
	//pDeviceContext->PSSetSamplers(0, 1, &m_pSpriteSampler);

	////���_�o�b�t�@�ݒ�
	//auto vertices = m_pSpriteVertices->getBuffer();
	//UINT stride = sizeof(SpriteVertex);
	//UINT offset = 0;
	//pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	////�C���f�b�N�X�o�b�t�@�ݒ�
	//pDeviceContext->IASetIndexBuffer(m_pSpriteIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	////�����_�[�^�[�Q�b�g����SRV�쐬
	//auto srv = m_RTLayers.at(GraphicsLayer::Default)->getSRV();
	//pDeviceContext->PSSetShaderResources(0, 1, &srv);

	////�萔�o�b�t�@�̍s��p�f�[�^���쐬
	//SpriteConstantBuffer spriteCBuffer;
	//auto translate = DirectX::XMMatrixTranslationFromVector(Camera::getPosition().toXMVector());
	//auto rotation = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	//auto scaling = DirectX::XMMatrixScaling(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f);
	//auto wvp = scaling * rotation * translate * Camera::getViewProjMatrix2D();
	//DirectX::XMStoreFloat4x4(&spriteCBuffer.wvpMatrix, DirectX::XMMatrixTranspose(wvp));

	////�萔�o�b�t�@�쐬
	//ConstantBuffer cBuffer;
	//cBuffer.init(DirectXManager::getDevice(), sizeof(SpriteConstantBuffer), &spriteCBuffer);

	////���_�V�F�[�_�[�ɒ萔�o�b�t�@�ݒ�
	//auto d3dConstantBuffer = cBuffer.getBuffer();
	//pDeviceContext->VSSetConstantBuffers(0, 1, &d3dConstantBuffer);

	//BlurConstantBuffer blurCBuffer;
	//blurCBuffer.texelSize = { 1.0f / Screen::getWindowWidth(), 1.0f / Screen::getWindowHeight(), 0.0f, 0.0f };
	//ConstantBuffer blurCBufferClass;
	//blurCBufferClass.init(DirectXManager::getDevice(), sizeof(BlurConstantBuffer), &blurCBuffer);
	//d3dConstantBuffer = blurCBufferClass.getBuffer();
	//pDeviceContext->PSSetConstantBuffers(0, 1, &d3dConstantBuffer);

	////�`��
	//pDeviceContext->DrawIndexed(6, 0, 0);

	//srv->Release();
}

void Renderer::postEffect2()
{
	//m_RTLayers.at(GraphicsLayer::Final)->setRenderTarget(false);

	//auto pDeviceContext = DirectXManager::getDeviceContext();
	////�V�F�[�_�[��ݒ�
	//pDeviceContext->VSSetShader(ShaderManager::GetVertexShaderInstance("SpriteVS"), nullptr, 0);
	//pDeviceContext->PSSetShader(ShaderManager::GetPixelShaderInstance("MetaBallPS"), nullptr, 0);

	////�摜�\���p��InputLayout��Sampler��ݒ�
	//pDeviceContext->IASetInputLayout(m_pSpriteInputLayout);
	//pDeviceContext->PSSetSamplers(0, 1, &m_pSpriteSampler);

	////���_�o�b�t�@�ݒ�
	//auto vertices = m_pSpriteVertices->getBuffer();
	//UINT stride = sizeof(SpriteVertex);
	//UINT offset = 0;
	//pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	////�C���f�b�N�X�o�b�t�@�ݒ�
	//pDeviceContext->IASetIndexBuffer(m_pSpriteIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	////�����_�[�^�[�Q�b�g����SRV�쐬
	//auto srv = m_RTLayers.at(GraphicsLayer::MetaBall)->getSRV();
	//pDeviceContext->PSSetShaderResources(0, 1, &srv);

	////�萔�o�b�t�@�̍s��p�f�[�^���쐬
	//SpriteConstantBuffer spriteCBuffer;
	//auto translate = DirectX::XMMatrixTranslationFromVector(Camera::getPosition().toXMVector());
	//auto rotation = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	//auto scaling = DirectX::XMMatrixScaling(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f);
	//auto wvp = scaling * rotation * translate * Camera::getViewProjMatrix2D();
	//DirectX::XMStoreFloat4x4(&spriteCBuffer.wvpMatrix, DirectX::XMMatrixTranspose(wvp));

	////�萔�o�b�t�@�쐬
	//ConstantBuffer cBuffer;
	//cBuffer.init(DirectXManager::getDevice(), sizeof(SpriteConstantBuffer), &spriteCBuffer);

	////���_�V�F�[�_�[�ɒ萔�o�b�t�@�ݒ�
	//auto d3dConstantBuffer = cBuffer.getBuffer();
	//pDeviceContext->VSSetConstantBuffers(0, 1, &d3dConstantBuffer);

	////�`��
	//pDeviceContext->DrawIndexed(6, 0, 0);

	//srv->Release();
}
