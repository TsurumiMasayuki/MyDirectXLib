#include "Mesh.h"
#include <fbxsdk.h>
#include "Device\DirectXManager.h"
#include "Device\Base\MeshVertex.h"
#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Resource\TextureManager.h"
#include "Utility\StringUtility.h"
#include <vector>

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

void Mesh::init(const std::string filePath, const std::wstring textureName)
{
	m_TextureName = StringUtility::toString(textureName);
	if (textureName != L"Default")
	{
		TextureManager::loadTexture(textureName.c_str(), m_TextureName);
	}

	//Fbx系の管理オブジェクトを作成
	FbxManager* pFbxManager = FbxManager::Create();
	//入出力設定
	FbxIOSettings* pIOSetting = FbxIOSettings::Create(pFbxManager, IOSROOT);
	pFbxManager->SetIOSettings(pIOSetting);
	//インポーター
	FbxImporter* pImporter = FbxImporter::Create(pFbxManager, "");

	//fbxをインポート
	bool isLoaded = pImporter->Initialize(filePath.c_str(), -1, pFbxManager->GetIOSettings());

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

	initVertices(pMesh);

	pFbxManager->Destroy();
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

void Mesh::initVertices(FbxMesh* pMesh)
{
	FbxStringList uvSetList;
	pMesh->GetUVSetNames(uvSetList);
	auto uvElem = pMesh->GetElementUV(uvSetList.GetStringAt(0));

	//UV座標の数で配列生成
	MeshVertex* vertices = new MeshVertex[pMesh->GetPolygonVertexCount()];
	int* indices = new int[pMesh->GetPolygonVertexCount()];

	//頂点バッファ用の情報を取得
	int vertexCount = pMesh->GetPolygonVertexCount() - 1;
	for (int i = 0; i < pMesh->GetPolygonCount(); ++i)
	{
		for (int j = 0; j < pMesh->GetPolygonSize(i); ++j)
		{
			int vertexIndex = pMesh->GetPolygonVertex(i, j);

			indices[vertexCount] = vertexCount;
			vertices[vertexCount].m_Pos.x = -(float)pMesh->GetControlPointAt(vertexIndex)[0];	//頂点のX成分を取得
			vertices[vertexCount].m_Pos.y = (float)pMesh->GetControlPointAt(vertexIndex)[1];	//頂点のY成分を取得
			vertices[vertexCount].m_Pos.z = (float)pMesh->GetControlPointAt(vertexIndex)[2];	//頂点のZ成分を取得

			FbxVector4 normal;
			pMesh->GetPolygonVertexNormal(i, j, normal);
			vertices[vertexCount].m_Normal.x = -(float)normal[0];	//法線のX成分を取得
			vertices[vertexCount].m_Normal.y = (float)normal[1];	//法線のY成分を取得
			vertices[vertexCount].m_Normal.z = (float)normal[2];	//法線のZ成分を取得

			FbxVector2 uv;
			bool isUnMapped = true;
			pMesh->GetPolygonVertexUV(i, j, uvSetList.GetStringAt(0), uv, isUnMapped);
			vertices[vertexCount].m_UV.x = (float)uv[0];	//UVのX成分を取得
			vertices[vertexCount].m_UV.y = 1 - (float)uv[1];	//UVのY成分を取得

			vertexCount--;
		}
	}

	//頂点ごとの情報を取得

	auto pDevice = DirectXManager::getDevice();

	//頂点バッファの作成
	if (m_pVertexBuffer != nullptr)
		delete m_pVertexBuffer;
	m_pVertexBuffer = new VertexBuffer();
	m_pVertexBuffer->init(pDevice, sizeof(MeshVertex) * uvElem->GetIndexArray().GetCount(), vertices);

	//不要になったので頂点データを解放
	delete vertices;

	//インデックスバッファの作成
	if (m_pIndexBuffer != nullptr)
		delete m_pIndexBuffer;
	m_pIndexBuffer = new IndexBuffer();
	m_pIndexBuffer->init(pDevice, sizeof(int) * uvElem->GetIndexArray().GetCount(), indices);

	//不要になったのでインデックスデータを解放
	delete indices;

	//頂点数を取得
	m_VertexCount = uvElem->GetIndexArray().GetCount();
}
