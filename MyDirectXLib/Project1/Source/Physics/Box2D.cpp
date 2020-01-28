#include "Box2D.h"

Box2D::Box2D()
	: m_Position(0.0f, 0.0f), 
	m_Width(0.0f),
	m_Height(0.0f),
	m_Angle(0.0f)
{
}

Box2D::~Box2D()
{
}

void Box2D::setSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Box2D::setSize(const Vec2 & size)
{
	m_Width = size.x;
	m_Height = size.y;
}

void Box2D::setAngle(float angle)
{
	m_Angle = angle;
}

float Box2D::getWidth() const
{
	return m_Width;
}

float Box2D::getHeight() const
{
	return m_Height;
}

float Box2D::getAngle() const
{
	return m_Angle;
}

Vec2 Box2D::getCenter() const
{
	return m_Position;
}

Vec2 Box2D::getLeftUp() const
{
	Vec2 position = m_Position;
	return position + Vec2(-m_Width * 0.5f, m_Height * 0.5f);
}

Vec2 Box2D::getLeftDown() const
{
	Vec2 position = m_Position;
	return position + Vec2(-m_Width * 0.5f, -m_Height * 0.5f);
}

Vec2 Box2D::getRightUp() const
{
	Vec2 position = m_Position;
	return position + Vec2(m_Width * 0.5f, m_Height * 0.5f);
}

Vec2 Box2D::getRightDown() const
{
	Vec2 position = m_Position;
	return position + Vec2(m_Width * 0.5f, -m_Height * 0.5f);
}

bool Box2D::isIntersect(const Box2D & box2D) const
{
	return false;
}

bool Box2D::isIntersect(const Circle2D & circle2D) const
{
	return false;
}