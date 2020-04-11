#ifndef _METABALLRENDERER_H_
#define _METABALLRENDERER_H_

#include <DirectXMath.h>
#include "Component\AbstractComponent.h"
#include "Component\Graphics\PostEffect\IPostEffectRenderer.h"

class VertexShader;
class PixelShader;
class VertexBuffer;
class IndexBuffer;
class RenderTarget;

struct ID3D11InputLayout;
struct ID3D11SamplerState;

class MetaBallRenderer
	: public AbstractComponent, public IPostEffectRenderer
{
public:
	MetaBallRenderer(GameObject* pUser);
	~MetaBallRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual void draw() override;

private:
	struct BasicVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

	struct BasicCBuffer
	{
		DirectX::XMFLOAT4X4 wvp;
	};

	struct MetaBallCBuffer
	{
		DirectX::XMFLOAT4 baseColor;
		DirectX::XMFLOAT4 outlineColor;
	};

private:
	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;

	VertexBuffer* m_pVertices;
	IndexBuffer* m_pIndices;

	ID3D11InputLayout* m_pInputLayout;
	ID3D11SamplerState* m_pSampler;

	RenderTarget* m_pSourceRT;
};

#endif