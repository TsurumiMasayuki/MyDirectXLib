#pragma once
#include <vector>

class IRenderer2D;
class MeshRenderer;

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

struct ID2D1Factory;
struct ID2D1RenderTarget;

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

	void addRenderer2D(IRenderer2D* pRenderer);
	void removeRenderer2D(IRenderer2D* pRenderer);

	//MeshRenderer��o�^����B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void addMesh(MeshRenderer* pMesh);
	//MeshRenderer�̓o�^����������B���������p�Ȃ̂Ŋ�{�g��Ȃ�
	void removeMesh(MeshRenderer* pMesh);

	ID2D1RenderTarget* getD2DRenderTarget() { return m_pD2DRenderTarget; };

private:
	void initBuffers();
	void initRenderTargets();

	void draw2D();
	void drawMeshes();

private:
	//���X�^���C�U
	ID3D11RasterizerState* m_pRasterizer;

	//�X�v���C�g�p
	ID3D11InputLayout* m_pSpriteInputLayout;
	ID3D11SamplerState* m_pSpriteSampler;
	VertexBuffer* m_pSpriteVertices;
	IndexBuffer* m_pSpriteIndices;

	//2D�R���|�[�l���g�Ǘ��pvector
	std::vector<IRenderer2D*> m_Renderer2DList;

	//3D���f���Ǘ��pvector
	std::vector<MeshRenderer*> m_Meshes;

	//3D���f���p
	ID3D11InputLayout* m_pMeshInputLayout;
	ID3D11SamplerState* m_pMeshSampler;

	//�����_�[�^�[�Q�b�g
	ID3D11Texture2D* m_pRenderTexDefault;
	ID3D11RenderTargetView* m_pRTVDefault;

	//�[�x�o�b�t�@
	ID3D11Texture2D* m_pDepthStencilTexture;
	ID3D11DepthStencilView* m_pDepthStencilView;

	//Direct2D�n
	ID2D1Factory* m_pD2DFactory;
	ID2D1RenderTarget* m_pD2DRenderTarget;
};