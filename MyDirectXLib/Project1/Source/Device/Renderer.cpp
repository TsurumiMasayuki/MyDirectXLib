#include "Renderer.h"
#include <d3d11.h>
#include <fbxsdk.h>
#include <DirectXMath.h>

#include "Def\Screen.h"

#include "Component\Graphics\SpriteRenderer.h"

#include "Device\Camera.h"
#include "Device\DirectXManager.h"
#include "Device\ShaderManager.h"

#include "Device\Base\SpriteVertex.h"
#include "Device\Base\ModelVertex.h"
#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"

#include "Device\Buffer\WVPConstantBuffer.h"
#include "Device\TextureManager.h"

#include "Math\MathUtility.h"

float x = 0.0f;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	m_pSpriteInputLayout->Release();
	delete m_pSpriteVertices;
	delete m_pSpriteIndices;

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

	//drawSprites();
	drawMeshes();

	DirectXManager::presentSwapChain();
}

void Renderer::addSprite(SpriteRenderer * pSprite)
{
	int myDrawOrder = pSprite->getDrawOrder();

	auto itr = m_Sprites.begin();
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

void Renderer::initBuffers()
{
#pragma region Sprite用
	D3D11_INPUT_ELEMENT_DESC inputDesc[2];
	SpriteVertex::getInputDesc(inputDesc);
	UINT numElements = 2;

	auto pDevice = DirectXManager::getDevice();

	ShaderManager::GetVertexShader("SpriteDefault")->createInputLayout(
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

	pBack->Release();
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

	//Fbx系の管理オブジェクトを作成
	FbxManager* pFbxManager = FbxManager::Create();
	//入出力設定
	FbxIOSettings* pIOSetting = FbxIOSettings::Create(pFbxManager, IOSROOT);
	pFbxManager->SetIOSettings(pIOSetting);
	//インポーター
	FbxImporter* pImporter = FbxImporter::Create(pFbxManager, "");

	std::string fileName = "Assets/Models/tekitou.fbx";
	//fbxをインポート
	if (!pImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings()))
	{
		//失敗したらfalseが返るのでエラー処理
	}

	//シーンの作成とインポート
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "myScene");
	pImporter->Import(pFbxScene);

	//インポートが終わったので破棄
	pImporter->Destroy();

	//メッシュデータ
	FbxMesh* pMesh = nullptr;
	//メッシュデータの取得
	for (int i = 0; i < pFbxScene->GetRootNode()->GetChildCount(); ++i)
	{
		//シーン内のノードを一個ずつ取得
		FbxNode* pChildNode = pFbxScene->GetRootNode()->GetChild(i);

		//ノードの種類がメッシュ用ならメッシュを取得
		if (pChildNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			pMesh = pChildNode->GetMesh();
			break;
		}
	}

	//コントロールポイント(頂点)の数で配列生成
	ModelVertex* vertices = new ModelVertex[pMesh->GetControlPointsCount()];
	//メッシュの頂点を全取得
	for (int i = 0; i < pMesh->GetControlPointsCount(); ++i)
	{
		vertices[i].m_Pos.x = (float)pMesh->GetControlPointAt(i)[0];	//頂点のX成分を取得
		vertices[i].m_Pos.y = (float)pMesh->GetControlPointAt(i)[1];	//頂点のY成分を取得
		vertices[i].m_Pos.z = (float)pMesh->GetControlPointAt(i)[2];	//頂点のZ成分を取得
		vertices[i].m_Pos.w = 1.0f;
	}

	//頂点バッファの作成
	D3D11_BUFFER_DESC verticesDesc;
	verticesDesc.ByteWidth = sizeof(ModelVertex) * pMesh->GetControlPointsCount();
	verticesDesc.Usage = D3D11_USAGE_DEFAULT;
	verticesDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	verticesDesc.CPUAccessFlags = 0;
	verticesDesc.MiscFlags = 0;
	verticesDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA verticesData;
	verticesData.pSysMem = vertices;

	ID3D11Buffer* pVertexBuffer;
	auto result = pDevice->CreateBuffer(&verticesDesc, &verticesData, &pVertexBuffer);

	//インデックスバッファの作成
	D3D11_BUFFER_DESC indicesDesc;
	indicesDesc.ByteWidth = sizeof(int) * pMesh->GetPolygonVertexCount();
	indicesDesc.Usage = D3D11_USAGE_DEFAULT;
	indicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indicesDesc.CPUAccessFlags = 0;
	indicesDesc.MiscFlags = 0;
	indicesDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indicesData;
	indicesData.pSysMem = pMesh->GetPolygonVertices();

	int polyCount = pMesh->GetPolygonCount();

	std::vector<int> indexVector;
	for (int i = 0; i < pMesh->GetPolygonCount(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			indexVector.emplace_back(pMesh->GetPolygonVertex(i, j));
		}
	}

	ID3D11Buffer* pIndexBuffer;
	pDevice->CreateBuffer(&indicesDesc, &indicesData, &pIndexBuffer);

	VertexShader meshVS("Assets/Shaders/MeshVS.cso");
	PixelShader meshPS("Assets/Shaders/MeshPS.cso");

	//インプットレイアウトの作成
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	ID3D11InputLayout* pInputLayout;
	meshVS.createInputLayout(pDevice, layout, 1, &pInputLayout);

	//定数バッファの作成
	D3D11_BUFFER_DESC constantDesc;
	constantDesc.ByteWidth = sizeof(WVPConstantBuffer);
	constantDesc.Usage = D3D11_USAGE_DEFAULT;
	constantDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantDesc.CPUAccessFlags = 0;
	constantDesc.MiscFlags = 0;
	constantDesc.StructureByteStride = 0;

	WVPConstantBuffer constantBuffer;
	//変換行列の作成
	DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationRollPitchYaw(MathUtility::toRadian(x), MathUtility::toRadian(x += 10), 0.0f);
	DirectX::XMMATRIX world = scale * rotate * translate;
	DirectX::XMMATRIX wvp = DirectX::XMMatrixTranspose(world * Camera::getViewProjMatrix3D());

	DirectX::XMStoreFloat4x4(&constantBuffer.wvpMatrix, wvp);

	D3D11_SUBRESOURCE_DATA constantData;
	constantData.pSysMem = &constantBuffer;

	ID3D11Buffer* pWVPBuffer;
	pDevice->CreateBuffer(&constantDesc, &constantData, &pWVPBuffer);

	//ラスタライザの作成
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = TRUE;

	ID3D11RasterizerState* pRasterizer;
	pDevice->CreateRasterizerState(&rasterDesc, &pRasterizer);

	UINT stride = sizeof(ModelVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetInputLayout(pInputLayout);
	pDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->VSSetShader(meshVS.getShader(), NULL, 0);
	pDeviceContext->PSSetShader(meshPS.getShader(), NULL, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &pWVPBuffer);
	pDeviceContext->RSSetState(pRasterizer);

	pDeviceContext->DrawIndexed(pMesh->GetPolygonVertexCount(), 0, 0);

	pFbxManager->Destroy();

	delete vertices;
}
