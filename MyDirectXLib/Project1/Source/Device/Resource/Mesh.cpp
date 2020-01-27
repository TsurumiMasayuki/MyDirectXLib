#include "Mesh.h"
#include <fbxsdk.h>
#include "Device\DirectXManager.h"
#include "Device\Base\MeshVertex.h"
#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"

#ifdef _DEBUG
#include <cassert>
#endif // _DEBUG

Mesh::Mesh()
	: m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr)
{
}

Mesh::~Mesh()
{
	delete m_pVertexBuffer;
	delete m_pIndexBuffer;
}

void Mesh::init(const char * filePath)
{
	//Fbx系の管理オブジェクトを作成
	FbxManager* pFbxManager = FbxManager::Create();
	//入出力設定
	FbxIOSettings* pIOSetting = FbxIOSettings::Create(pFbxManager, IOSROOT);
	pFbxManager->SetIOSettings(pIOSetting);
	//インポーター
	FbxImporter* pImporter = FbxImporter::Create(pFbxManager, "");

	std::string fileName = filePath;

	//fbxをインポート
	bool isLoaded = pImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

#ifdef _DEBUG
	//失敗したらfalseが返るのでエラー処理
	assert(isLoaded);
#endif

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
	MeshVertex* vertices = new MeshVertex[pMesh->GetPolygonVertexCount()];

	//メッシュの頂点を全取得
	for (int i = 0; i < pMesh->GetControlPointsCount(); ++i)
	{
		vertices[i].m_Pos.x = (float)pMesh->GetControlPointAt(i)[0];	//頂点のX成分を取得
		vertices[i].m_Pos.y = (float)pMesh->GetControlPointAt(i)[1];	//頂点のY成分を取得
		vertices[i].m_Pos.z = (float)pMesh->GetControlPointAt(i)[2];	//頂点のZ成分を取得
		vertices[i].m_Pos.w = (float)pMesh->GetControlPointAt(i)[3];	//頂点のW成分を取得
	}

	//法線ベクトルを取得
	int count = 0;
	for (int i = 0; i < pMesh->GetPolygonCount(); ++i)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			FbxVector4 normal;
			pMesh->GetPolygonVertexNormal(i, j, normal);
			vertices[count].m_Normal.x = (float)normal[0];
			vertices[count].m_Normal.y = (float)normal[1];
			vertices[count].m_Normal.z = (float)normal[2];
			vertices[count].m_Normal.w = (float)normal[3];
			count++;
		}
	}

	auto pDevice = DirectXManager::getDevice();

	//頂点バッファの作成
	if (m_pVertexBuffer != nullptr)
		delete m_pVertexBuffer;
	m_pVertexBuffer = new VertexBuffer();
	m_pVertexBuffer->init(pDevice, sizeof(MeshVertex) * pMesh->GetControlPointsCount(), vertices);

	//インデックスバッファの作成
	if (m_pIndexBuffer != nullptr)
		delete m_pIndexBuffer;
	m_pIndexBuffer = new IndexBuffer();
	m_pIndexBuffer->init(pDevice, sizeof(int) * pMesh->GetPolygonVertexCount(), pMesh->GetPolygonVertices());

	//頂点数を取得
	m_VertexCount = pMesh->GetPolygonVertexCount();

	pFbxManager->Destroy();
	delete[] vertices;
}

const VertexBuffer & Mesh::getVertexBuffer()
{
	return *m_pVertexBuffer;
}

const IndexBuffer & Mesh::getIndexBuffer()
{
	return *m_pIndexBuffer;
}

int Mesh::getVertexCount()
{
	return m_VertexCount;
}
