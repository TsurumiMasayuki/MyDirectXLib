#pragma once
#include <vector>
#include <unordered_map>
#include <DirectXMath.h>
#include "Component\Graphics\GraphicsLayer.h"

class IRenderer2D;
class MeshRenderer;

class RenderTarget;

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

struct ID2D1Factory;
struct ID2D1RenderTarget;

struct ID3D11InputLayout;
struct ID3D11RasterizerState;
struct ID3D11SamplerState;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void draw();

	void addRenderer2D(IRenderer2D* pRenderer);
	void removeRenderer2D(IRenderer2D* pRenderer);

	//MeshRendererを登録する。内部処理用なので基本使わない
	void addMesh(MeshRenderer* pMesh);
	//MeshRendererの登録を解除する。内部処理用なので基本使わない
	void removeMesh(MeshRenderer* pMesh);

	ID2D1RenderTarget* getD2DRenderTarget() { return m_pD2DRenderTarget; };

private:
	void initBuffers();
	void initRenderTargets();

	void draw2D();
	void drawMeshes();
	void postEffect();
	void postEffect2();

private:
	//レンダーターゲット
	std::unordered_map<GraphicsLayer, RenderTarget*> m_RTLayers;

	//ラスタライザ
	ID3D11RasterizerState* m_pRasterizer;

	//スプライト用
	ID3D11InputLayout* m_pSpriteInputLayout;
	ID3D11SamplerState* m_pSpriteSampler;
	VertexBuffer* m_pSpriteVertices;
	IndexBuffer* m_pSpriteIndices;

	//2Dコンポーネント管理用vector
	std::vector<IRenderer2D*> m_Renderer2DList;

	//3Dモデル管理用vector
	std::vector<MeshRenderer*> m_Meshes;

	//3Dモデル用
	ID3D11InputLayout* m_pMeshInputLayout;
	ID3D11SamplerState* m_pMeshSampler;

	//Direct2D系
	ID2D1Factory* m_pD2DFactory;
	ID2D1RenderTarget* m_pD2DRenderTarget;

	struct BlurConstantBuffer
	{
		DirectX::XMFLOAT4 texelSize;
	};
};