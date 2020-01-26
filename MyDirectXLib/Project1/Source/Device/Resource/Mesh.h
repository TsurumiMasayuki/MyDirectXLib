#pragma once

struct VertexBuffer;
struct IndexBuffer;

//メッシュ用構造体
struct Mesh
{
public:
	Mesh();
	~Mesh();

	//初期化処理
	void init(const char* filePath);

	//頂点バッファの取得
	const VertexBuffer& getVertexBuffer();
	//インデックスバッファの取得
	const IndexBuffer& getIndexBuffer();

	int getVertexCount();

private:
	//コピー禁止
	Mesh(const Mesh&) = delete;
	void operator = (const Mesh&) = delete;

private:
	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	int m_VertexCount;
};