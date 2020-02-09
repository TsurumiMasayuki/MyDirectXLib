#pragma once
#include <string>

struct VertexBuffer;
struct IndexBuffer;

namespace fbxsdk
{
	class FbxMesh;
}

//メッシュ用構造体
struct Mesh
{
public:
	Mesh();
	~Mesh();

	//初期化処理
	void init(const std::string filePath, const std::wstring textureName = L"Default");

	//頂点バッファの取得
	const VertexBuffer& getVertexBuffer();
	//インデックスバッファの取得
	const IndexBuffer& getIndexBuffer();

	//テクスチャ名の取得
	std::string getTextureName() { return m_TextureName; };

	int getVertexCount();

private:
	void initVertices(fbxsdk::FbxMesh* pMesh);

private:
	//コピー禁止
	Mesh(const Mesh&) = delete;
	void operator = (const Mesh&) = delete;

private:
	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	int m_VertexCount;
	std::string m_TextureName;
};