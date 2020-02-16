#pragma once
#include <vector>

class SpriteRenderer;
class MeshRenderer;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

struct ID3D11InputLayout;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;
struct ID3D11RasterizerState;
struct ID3D11SamplerState;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void draw();

	//SpriteRendererを登録する。内部処理用なので基本使わない
	void addSprite(SpriteRenderer* pSprite);
	//SpriteRendererの登録を解除する。内部処理用なので基本使わない
	void removeSprite(SpriteRenderer* pSprite);

	//MeshRendererを登録する。内部処理用なので基本使わない
	void addMesh(MeshRenderer* pMesh);
	//MeshRendererの登録を解除する。内部処理用なので基本使わない
	void removeMesh(MeshRenderer* pMesh);

private:
	void initBuffers();
	void initRenderTargets();

	void drawSprites();
	void drawMeshes();

private:
	//ラスタライザ
	ID3D11RasterizerState* m_pRasterizer;

	//スプライト管理用vector
	std::vector<SpriteRenderer*> m_Sprites;

	//スプライト用
	ID3D11InputLayout* m_pSpriteInputLayout;
	ID3D11SamplerState* m_pSpriteSampler;
	VertexBuffer* m_pSpriteVertices;
	IndexBuffer* m_pSpriteIndices;

	//3Dモデル管理用vector
	std::vector<MeshRenderer*> m_Meshes;

	//3Dモデル用
	ID3D11InputLayout* m_pMeshInputLayout;
	ID3D11SamplerState* m_pMeshSampler;

	//レンダーターゲット
	ID3D11Texture2D* m_pRenderTexDefault;
	ID3D11RenderTargetView* m_pRTVDefault;

	//深度バッファ
	ID3D11Texture2D* m_pDepthStencilTexture;
	ID3D11DepthStencilView* m_pDepthStencilView;
};