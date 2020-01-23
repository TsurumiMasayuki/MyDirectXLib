#pragma once
class AbstractCollider2D;
class BoxCollider2D;
class CircleCollider2D;

namespace PhysicsCalc
{
	bool isCollision2D(BoxCollider2D* pBox1, BoxCollider2D* pBox2);
	bool isCollision2D(CircleCollider2D* pCircle1, CircleCollider2D* pCircle2);

	bool isCollision2D(BoxCollider2D* pBox, CircleCollider2D* pCircle);
	bool isCollision2D(CircleCollider2D* pCircle, BoxCollider2D* pBox);

	void fixPosition2D(BoxCollider2D* pBox1, BoxCollider2D* pBox2);
	void fixPosition2D(CircleCollider2D* pCircle1, CircleCollider2D* pCircle2);

	void fixPosition2D(BoxCollider2D* pBox, CircleCollider2D* pCircle);
	void fixPosition2D(CircleCollider2D* pCircle, BoxCollider2D* pBox);

	bool boxIntersect2D(float x1, float y1, float x2, float y2);
}