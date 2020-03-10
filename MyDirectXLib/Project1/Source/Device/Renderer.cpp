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
	m_pSpriteInputLayout->Release();
	m_pSpriteSampler->Release();
	delete m_pSpriteVertices;
	delete m_pSpriteIndices;

	delete m_pRenderTargetDefault;
	delete m_pRenderTargetFinal;

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

	//SwapChainからバックバッファを取得
	IDXGISurface* pBack;
	//DirectXManager::getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBack);

	FLOAT dpiX;
	FLOAT dpiY;
	m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	D2D1_RENDER_TARGET_PROPERTIES rtProp =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX, dpiY
		);

	//レンダーターゲットからテキスト書き込み用のテクスチャ取得
	m_pRenderTargetDefault->getRenderTexture()->QueryInterface(__uuidof(IDXGISurface), (LPVOID*)&pBack);
	m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBack, rtProp, &m_pD2DRenderTarget);
}

void Renderer::draw()
{
	//レンダーターゲットをクリア
	m_pRenderTargetDefault->clearRenderTarget();
	m_pRenderTargetFinal->clearRenderTarget();

	drawMeshes();
	draw2D();

	m_pRenderTargetFinal->setRenderTarget(true);

	auto pDeviceContext = DirectXManager::getDeviceContext();
	//シェーダーを設定
	pDeviceContext->VSSetShader(ShaderManager::GetVertexShaderInstance("SpriteVS"), nullptr, 0);
	pDeviceContext->PSSetShader(ShaderManager::GetPixelShaderInstance("BlurPS"), nullptr, 0);

	//画像表示用のInputLayoutとSamplerを設定
	pDeviceContext->IASetInputLayout(m_pSpriteInputLayout);
	pDeviceContext->PSSetSamplers(0, 1, &m_pSpriteSampler);

	//頂点バッファ設定
	auto vertices = m_pSpriteVertices->getBuffer();
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	//インデックスバッファ設定
	pDeviceContext->IASetIndexBuffer(m_pSpriteIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//レンダーターゲットからSRV作成
	auto srv = m_pRenderTargetDefault->getSRV();
	pDeviceContext->PSSetShaderResources(0, 1, &srv);

	//定数バッファの行列用データを作成
	SpriteConstantBuffer spriteCBuffer;
	auto translate = DirectX::XMMatrixTranslationFromVector(Camera::getPosition().toXMVector());
	auto rotation = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	auto scaling = DirectX::XMMatrixScaling(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f);
	auto wvp = scaling * rotation * translate * Camera::getViewProjMatrix2D();
	DirectX::XMStoreFloat4x4(&spriteCBuffer.wvpMatrix, DirectX::XMMatrixTranspose(wvp));

	//定数バッファ作成
	ConstantBuffer cBuffer;
	cBuffer.init(DirectXManager::getDevice(), sizeof(SpriteConstantBuffer), &spriteCBuffer);

	//頂点シェーダーに定数バッファ設定
	auto d3dConstantBuffer = cBuffer.getBuffer();
	pDeviceContext->VSSetConstantBuffers(0, 1, &d3dConstantBuffer);

	BlurConstantBuffer blurCBuffer;
	blurCBuffer.texelSize = { 1.0f / Screen::getWindowWidth(), 1.0f / Screen::getWindowHeight(), 0.0f, 0.0f };
	ConstantBuffer blurCBufferClass;
	blurCBufferClass.init(DirectXManager::getDevice(), sizeof(BlurConstantBuffer), &blurCBuffer);
	d3dConstantBuffer = blurCBufferClass.getBuffer();
	pDeviceContext->PSSetConstantBuffers(0, 1, &d3dConstantBuffer);

	//描画
	pDeviceContext->DrawIndexed(6, 0, 0);

	DirectXManager::presentSwapChain();

	srv->Release();
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

	//通常描画用RTV作成
	m_pRenderTargetDefault = new RenderTarget(Screen::getWindowWidth(), Screen::getWindowHeight());
	m_pRenderTargetDefault->setClearColor(Color(0.0f, 0.0f, 0.0f, 1.0f));

	//SwapChainからバックバッファを取得
	ID3D11Texture2D* pBack;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);
	//画面描画用RTV作成
	m_pRenderTargetFinal = new RenderTarget(pBack);
	m_pRenderTargetFinal->setClearColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
}

void Renderer::draw2D()
{
	auto pDeviceContext = DirectXManager::getDeviceContext();

	//通常描画用レンダーターゲットを深度バッファ無しでセット
	m_pRenderTargetDefault->setRenderTarget(false);

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
	m_pRenderTargetDefault->setRenderTarget(true);

	pDeviceContext->IASetInputLayout(m_pMeshInputLayout);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->RSSetState(m_pRasterizer);
	pDeviceContext->PSSetSamplers(0, 1, &m_pMeshSampler);

	for (auto mesh : m_Meshes)
	{
		mesh->draw();
	}
}
