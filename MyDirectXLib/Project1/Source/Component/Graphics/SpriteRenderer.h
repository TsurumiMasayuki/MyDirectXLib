#pragma once
#include "Component\AbstractComponent.h"
#include "Component\Graphics\IRenderer2D.h"
#include "Utility\Color.h"
#include "Math\Vec2.h"
#include "Math\RectF.h"
#include <string>

class Renderer;
class ConstantBuffer;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;

struct ID3D11InputLayout;
struct ID3D11SamplerState;
struct ID3D11ShaderResourceView;

class SpriteRenderer
	: public AbstractComponent, public IRenderer2D
{
public:
	SpriteRenderer(GameObject* pUser, int drawOrder = 100);
	~SpriteRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual int getDrawOrder() const override { return m_DrawOrder; }
	virtual GraphicsLayer getGraphicsLayer() const override { return m_GraphicsLayer; }
	virtual void draw() override;

	void setTexture(ID3D11ShaderResourceView* pSRV);
	void setTextureByName(const std::string& textureName);

	void setColor(Color color);
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);

	Vec2 getPivot();
	void setPivot(Vec2 pivot);

	RectF getUVRect();
	void setUVRect(RectF uvRect);

	void setGraphicsLayer(GraphicsLayer graphicsLayer) { m_GraphicsLayer = graphicsLayer; }

private:
	int m_DrawOrder;

	ID3D11ShaderResourceView* m_pSRV;
	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;

	Color m_Color;
	bool m_FlipX;
	bool m_FlipY;

	Vec2 m_ImagePivot;
	RectF m_UVRect;

	GraphicsLayer m_GraphicsLayer;

	static int componentCount;

	static ID3D11InputLayout* pInputLayout;
	static ID3D11SamplerState* pSampler;
	static VertexBuffer* pVertices;
	static IndexBuffer* pIndices;
	static ConstantBuffer* pSpriteCB;
};