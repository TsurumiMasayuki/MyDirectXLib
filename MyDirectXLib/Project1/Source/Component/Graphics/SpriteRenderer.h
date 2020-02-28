#pragma once
#include "Component\AbstractComponent.h"
#include "Component\Graphics\IRenderer2D.h"
#include "Utility\Color.h"
#include "Math\Vec2.h"
#include "Math\RectF.h"
#include <string>

class Renderer;
class ConstantBuffer;

class SpriteRenderer
	: public AbstractComponent, public IRenderer2D
{
public:
	SpriteRenderer(GameObject* pUser, int drawOrder = 100);
	~SpriteRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;

	virtual int getDrawOrder() const override { return m_DrawOrder; }
	virtual void draw() override;

	void setTextureName(const std::string textureName);
	std::string getTextureName();

	void setColor(Color color);
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);

	Vec2 getPivot();
	void setPivot(Vec2 pivot);

	RectF getUVRect();
	void setUVRect(RectF uvRect);

private:
	int m_DrawOrder;

	std::string m_TextureName;
	std::string m_VSName;
	std::string m_PSName;

	Color m_Color;
	bool m_FlipX;
	bool m_FlipY;

	Vec2 m_ImagePivot;
	RectF m_UVRect;

	static unsigned int componentCount;
	static ConstantBuffer* pSpriteCB;
};