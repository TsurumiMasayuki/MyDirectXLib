#pragma once
class AbstractCollider2D;
class BoxCollider2D;
class CircleCollider2D;

class Box3D;
class Sphere3D;

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

	bool isIntersect3D(const Sphere3D& sphere1, const Sphere3D& sphere2);

	void fixPosition3D(Sphere3D& sphere1, const Sphere3D& sphere2);
}