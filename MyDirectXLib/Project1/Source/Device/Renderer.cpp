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

#include "WindowInstance.h"

#include "Device\Camera.h"
#include "Device\DirectXManager.h"

#include "Device\Base\SpriteVertex.h"
#include "Device\Base\MeshVertex.h"
#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"

#include "Device\Buffer\WVPConstantBuffer.h"
#include "Device\Resource\Shader\VertexShader.h"
#include "Device\Resource\Shader\PixelShader.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\TextureManager.h"

#include "Math\MathUtility.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	m_pSpriteInputLayout->Release();
	m_pSpriteSampler->Release();
	delete m_pSpriteVertices;
	delete m_pSpriteIndices;

	m_pMeshInputLayout->Release();
	m_pMeshSampler->Release();

	m_pRenderTexDefault->Release();
	m_pRTVDefault->Release();

	m_pDepthStencilTexture->Release();
	m_pDepthStencilView->Release();

	m_pD2DFactory->Release();
	m_pD2DRenderTarget->Release();
}

void Renderer::init()
{
	initBuffers();
	initRenderTargets();

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	//SwapChainからバックバッファを取得
	IDXGISurface* pBack;
	DirectXManager::getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBack);

	FLOAT dpiX;
	FLOAT dpiY;
	m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES rtProp =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX, dpiY
		);
	m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBack, rtProp, &m_pD2DRenderTarget);
}

void Renderer::draw()
{
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	float clearColor[4] = { 0, 0.5f, 0.75f, 1 };

	//レンダーターゲットをクリア
	pDeviceContext->ClearRenderTargetView(m_pRTVDefault, clearColor);
	//深度バッファをクリア
	pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	drawMeshes();
	draw2D();

	DirectXManager::presentSwapChain();
}

void Renderer::addRenderer2D(IRenderer2D * pRenderer)
{
	int myDrawOrder = pRenderer->getDrawOrder();

	auto itr = m_Renderer2DList.begin();
	//自分よりDrawOrderが高くなるまでループ
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
	//自分よりDrawOrderが高くなるまでループ
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

void Renderer::initBuffers()
{
#pragma region Sprite用
	D3D11_INPUT_ELEMENT_DESC inputDesc[2];
	SpriteVertex::getInputDesc(inputDesc);
	UINT numElements = 2;

	auto pDevice = DirectXManager::getDevice();

	ShaderManager::GetVertexShader("SpriteVS")->createInputLayout(
		pDevice,
		inputDesc,
		2,
		&m_pSpriteInputLayout
	);

	float width = 0.5f;
	float height = 0.5f;

	//四角の頂点情報作成
	SpriteVertex vertices[]
	{
		{{-width,  height, 0.0f}, {0.0f, 0.0f}},
		{{ width, -height, 0.0f}, {1.0f, 1.0f}},
		{{-width, -height, 0.0f}, {0.0f, 1.0f}},
		{{ width,  height, 0.0f}, {1.0f, 0.0f}},
	};

	m_pSpriteVertices = new VertexBuffer();
	m_pSpriteVertices->init(pDevice, sizeof(SpriteVertex) * 4, vertices);

	UINT indices[]
	{
		0, 1, 2,
		0, 3, 1
	};

	m_pSpriteIndices = new IndexBuffer();
	m_pSpriteIndices->init(pDevice, sizeof(UINT) * 6, indices);

	//サンプラーの作成(スプライト用)
	D3D11_SAMPLER_DESC spriteSamDesc;
	ZeroMemory(&spriteSamDesc, sizeof(D3D11_SAMPLER_DESC));
	spriteSamDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	spriteSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	spriteSamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	pDevice->CreateSamplerState(&spriteSamDesc, &m_pSpriteSampler);
#pragma endregion

#pragma region Mesh用

	//インプットレイアウトの作成
	D3D11_INPUT_ELEMENT_DESC layout[3];
	MeshVertex::getInputDesc(layout);
	ShaderManager::GetVertexShader("MeshVS")->createInputLayout(pDevice, layout, 3, &m_pMeshInputLayout);

	//ラスタライザの作成
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_FRONT;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = TRUE;

	pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizer);

	//サンプラーの作成(3Dモデル用)
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

	//ビューポートを設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (float)Screen::getWindowWidth();
	vp.Height = (float)Screen::getWindowHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	pDeviceContext->RSSetViewports(1, &vp);

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = (float)Screen::getWindowWidth();
	texDesc.Height = (float)Screen::getWindowHeight();
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	//レンダーテクスチャ作成
	pDevice->CreateTexture2D(&texDesc, NULL, &m_pRenderTexDefault);	//通常描画

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	//レンダーターゲット作成
	pDevice->CreateRenderTargetView(m_pRenderTexDefault, &rtvDesc, &m_pRTVDefault);		//通常描画

	//深度バッファ作成
	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthTexDesc.Width = Screen::getWindowWidth();
	depthTexDesc.Height = Screen::getWindowHeight();
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;

	pDevice->CreateTexture2D(&depthTexDesc, NULL, &m_pDepthStencilTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthViewDesc.Format = depthTexDesc.Format;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Texture2D.MipSlice = 0;

	pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &depthViewDesc, &m_pDepthStencilView);

	//SwapChainからバックバッファを取得
	ID3D11Texture2D* pBack;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);
	//画面描画用RTV作成
	pDevice->CreateRenderTargetView(pBack, NULL, &m_pRTVDefault);
}

void Renderer::draw2D()
{
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//通常描画用レンダーターゲットを深度バッファ無しでセット
	pDeviceContext->OMSetRenderTargets(1, &m_pRTVDefault, NULL);

	pDeviceContext->IASetInputLayout(m_pSpriteInputLayout);
	pDeviceContext->PSSetSamplers(0, 1, &m_pSpriteSampler);

	auto vertices = m_pSpriteVertices->getBuffer();
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(m_pSpriteIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//文字の描画
	m_pD2DRenderTarget->BeginDraw();
	for (auto renderer2D : m_Renderer2DList)
	{
		renderer2D->draw();
	}
	m_pD2DRenderTarget->EndDraw();
}

void Renderer::drawMeshes()
{
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//通常描画用レンダーターゲットを深度バッファ付きでセット
	pDeviceContext->OMSetRenderTargets(1, &m_pRTVDefault, m_pDepthStencilView);

	pDeviceContext->IASetInputLayout(m_pMeshInputLayout);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->RSSetState(m_pRasterizer);
	pDeviceContext->PSSetSamplers(0, 1, &m_pMeshSampler);

	for (auto mesh : m_Meshes)
	{
		mesh->draw();
	}
}
