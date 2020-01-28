#pragma once
#include "Physics\IShape2D.h"
#include "Math\Vec2.h"

class Box2D
	: public IShape2D
{
public:
	Box2D();
	~Box2D();

	void setSize(float width, float height);
	void setSize(const Vec2& size);
	void setAngle(float angle);

	float getWidth() const;
	float getHeight() const;
	float getAngle() const;

	//四角形の中心
	Vec2 getCenter() const;
	//四角形の左上
	Vec2 getLeftUp() const;
	//四角形の左下
	Vec2 getLeftDown() const;
	//四角形の右上
	Vec2 getRightUp() const;
	//四角形の右下
	Vec2 getRightDown() const;

	virtual bool isIntersect(const Box2D & box2D) const override;
	virtual bool isIntersect(const Circle2D & circle2D)  const override;

private:
	Vec2 m_Position;

	float m_Width;
	float m_Height;

	float m_Angle;
};