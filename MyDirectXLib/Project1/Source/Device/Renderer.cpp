#include "Renderer.h"
#include <d3d11.h>
#include <fbxsdk.h>
#include <DirectXMath.h>

#include "Def\Screen.h"

#include "Component\Graphics\SpriteRenderer.h"
#include "Component\Graphics\MeshRenderer.h"

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
	delete m_pSpriteVertices;
	delete m_pSpriteIndices;

	m_pMeshInputLayout->Release();

	m_pRenderTexDefault->Release();

	m_pRTVDefault->Release();
}

void Renderer::init()
{
	initBuffers();
	initRenderTargets();
}

void Renderer::draw()
{
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	float clearColor[4] = { 0, 0.5f, 0.75f, 1 };

	//レンダーターゲットをクリア
	pDeviceContext->ClearRenderTargetView(m_pRTVDefault, clearColor);

	//通常描画用レンダーターゲットをセット
	pDeviceContext->OMSetRenderTargets(1, &m_pRTVDefault, NULL);

	drawSprites();
	drawMeshes();

	DirectXManager::presentSwapChain();
}

void Renderer::addSprite(SpriteRenderer * pSprite)
{
	int myDrawOrder = pSprite->getDrawOrder();

	auto itr = m_Sprites.begin();
	//自分よりDrawOrderが高くなるまでループ
	while (itr != m_Sprites.end())
	{
		if (myDrawOrder < (*itr)->getDrawOrder())
			break;

		++itr;
	}

	m_Sprites.insert(itr, pSprite);
}

void Renderer::removeSprite(SpriteRenderer * pSprite)
{
	auto itr = std::find(m_Sprites.begin(), m_Sprites.end(), pSprite);
	m_Sprites.erase(itr);
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
#pragma endregion

#pragma region Mesh用

	//インプットレイアウトの作成
	D3D11_INPUT_ELEMENT_DESC layout[1];
	MeshVertex::getInputDesc(layout);
	ShaderManager::GetVertexShader("MeshVS")->createInputLayout(pDevice, layout, 1, &m_pMeshInputLayout);

	//ラスタライザの作成
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = TRUE;

	pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizer);

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

	//SRV作成
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;

	pDevice->CreateShaderResourceView(m_pRenderTexDefault, &viewDesc, &m_pSRVDefault);

	//SwapChainからバックバッファを取得
	ID3D11Texture2D* pBack;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack);
	//画面描画用RTV作成
	pDevice->CreateRenderTargetView(pBack, NULL, &m_pRTVDefault);
}

void Renderer::drawSprites()
{
	auto pDeviceContext = DirectXManager::getDeviceContext();

	pDeviceContext->IASetInputLayout(m_pSpriteInputLayout);

	auto vertices = m_pSpriteVertices->getBuffer();
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(m_pSpriteIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);

	for (auto sprite : m_Sprites)
	{
		sprite->draw();
	}
}

void Renderer::drawMeshes()
{
	auto pDevice = DirectXManager::getDevice();
	auto pDeviceContext = DirectXManager::getDeviceContext();

	pDeviceContext->IASetInputLayout(m_pMeshInputLayout);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->RSSetState(m_pRasterizer);

	for (auto mesh : m_Meshes)
	{
		mesh->draw();
	}
}
