#ifndef _DEFAULTRENDER_H_
#define _DEFAULTRENDER_H_

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

class DefaultRender
	: public AbstractComponent, public IPostEffectRenderer
{
public:
	DefaultRender(GameObject* pUser, int drawOrder, GraphicsLayer sourceLayer, GraphicsLayer destLayer = GraphicsLayer::Final);
	~DefaultRender();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual int getDrawOrder() const override { return m_DrawOrder; }
	virtual GraphicsLayer getDestLayer() const override { return m_DestLayer; }

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

private:
	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;

	VertexBuffer* m_pVertices;
	IndexBuffer* m_pIndices;

	ID3D11InputLayout* m_pInputLayout;
	ID3D11SamplerState* m_pSampler;

	RenderTarget* m_pSourceRT;

	GraphicsLayer m_SourceLayer;
	GraphicsLayer m_DestLayer;

	int m_DrawOrder;
};

#endif