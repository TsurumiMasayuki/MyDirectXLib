#pragma once
#include <vector>
#include <unordered_map>
#include <DirectXMath.h>
#include "Component\Graphics\GraphicsLayer.h"

class IRenderer2D;
class MeshRenderer;
class IPostEffectRenderer;

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

	//2D�p�`��R���|�[�l���g��o�^����B���������p
	void addRenderer2D(IRenderer2D* pRenderer);
	//2D�p�`��R���|�[�l���g��o�^��������B���������p
	void removeRenderer2D(IRenderer2D* pRenderer);

	//MeshRenderer��o�^����B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void addMesh(MeshRenderer* pMesh);
	//MeshRenderer�̓o�^����������B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void removeMesh(MeshRenderer* pMesh);

	//PostEffect�p�R���|�[�l���g��o�^����B���������p
	void addPostEffect(IPostEffectRenderer* pPostEffect);
	//PostEffect�p�R���|�[�l���g��o�^��������B���������p
	void removePostEffect(IPostEffectRenderer* pPostEffect);

	ID2D1RenderTarget* getD2DRenderTarget() { return m_pD2DRenderTarget; }

	RenderTarget* getRenderTarget(GraphicsLayer graphicsLayer) { return m_RTLayers.at(graphicsLayer); }

private:
	void initBuffers();
	void initRenderTargets();

	void draw2D();
	void drawMeshes();
	void drawPostEffects();

private:
	//�����_�[�^�[�Q�b�g
	std::unordered_map<GraphicsLayer, RenderTarget*> m_RTLayers;

	//���X�^���C�U
	ID3D11RasterizerState* m_pRasterizer;

	//2D�R���|�[�l���g�Ǘ��pvector
	std::vector<IRenderer2D*> m_Renderer2DList;

	//3D���f���Ǘ��pvector
	std::vector<MeshRenderer*> m_Meshes;

	//�|�X�g�G�t�F�N�g�Ǘ��pvector
	std::vector<IPostEffectRenderer*> m_PostEffects;

	//3D���f���p
	ID3D11InputLayout* m_pMeshInputLayout;
	ID3D11SamplerState* m_pMeshSampler;

	//Direct2D�n
	ID2D1Factory* m_pD2DFactory;
	ID2D1RenderTarget* m_pD2DRenderTarget;

	struct BlurConstantBuffer
	{
		DirectX::XMFLOAT4 texelSize;
	};
};