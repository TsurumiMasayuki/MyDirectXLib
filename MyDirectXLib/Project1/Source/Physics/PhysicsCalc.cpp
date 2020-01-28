#include "PhysicsCalc.h"
#include "Actor\GameObject.h"
#include "Math\MathUtility.h"
#include "Component\Physics\CircleCollider2D.h"
#include "Component\Physics\BoxCollider2D.h"
#include "Math\Vec2.h"

enum HitDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

HitDirection getHitDirection(BoxCollider2D* pBox1, BoxCollider2D* pBox2)
{
	HitDirection hitDir = HitDirection::UP;

	Vec3 direction = pBox2->position() - pBox1->position();

	float curXDistance = std::fabsf(direction.x);
	float curYDisntace = std::fabsf(direction.y);

	float minXDistance = (pBox1->getWidth() + pBox2->getWidth()) * 0.5f;
	float minYDistance = (pBox1->getHeight() + pBox2->getHeight())* 0.5f;

	float xPercent = curXDistance / minXDistance;
	float yPercent = curYDisntace / minYDistance;

	if (xPercent > yPercent)
	{
		if (direction.x > 0)
			hitDir = HitDirection::RIGHT;
		else
			hitDir = HitDirection::LEFT;
	}
	else
	{
		if (direction.y > 0)
			hitDir = HitDirection::UP;
		else
			hitDir = HitDirection::DOWN;
	}

	return hitDir;
}

bool PhysicsCalc::isCollision2D(BoxCollider2D * pBox1, BoxCollider2D * pBox2)
{
	Vec3 position = pBox1->getUser()->getPosition();
	Vec3 otherPos = pBox2->getUser()->getPosition();

	//現在のX,Yそれぞれの距離の絶対値を算出
	const float xDiff = std::fabsf(position.x - otherPos.x);
	const float yDiff = std::fabsf(position.y - otherPos.y);

	//衝突までの最短距離と現在の距離の比較を横、縦それぞれで行う
	return
		xDiff < (pBox1->getWidth() + pBox2->getWidth()) * 0.5f &&
		yDiff < (pBox1->getHeight() + pBox2->getHeight()) * 0.5f;
}

bool PhysicsCalc::isCollision2D(CircleCollider2D * pCircle1, CircleCollider2D * pCircle2)
{
	float sqrDistance = pCircle1->position().sqrDistance(pCircle2->position());
	float minRadius2 = std::powf(pCircle1->getRadius() + pCircle2->getRadius(), 2);
	return sqrDistance < minRadius2;
}

bool PhysicsCalc::isCollision2D(BoxCollider2D * pBox, CircleCollider2D * pCircle)
{
	float compareValue = fmaxf(pBox->getWidth(), pBox->getHeight()) / 2;
	compareValue = std::powf(compareValue + pCircle->getRadius(), 2);

	if (!(pCircle->position().sqrDistance(pBox->position()) < compareValue))
	{
		return false;
	}

	Vec2 rotate = Vec2::rotateBy(pCircle->position().toVec2(), pBox->position().toVec2(), -pBox->angles().z);
	float xPrime = rotate.x;
	float yPrime = rotate.y;

	float left = pBox->position().x - pBox->getWidth() / 2;
	float right = pBox->position().x + pBox->getWidth() / 2;

	float up = pBox->position().y + pBox->getHeight() / 2;
	float down = pBox->position().y - pBox->getHeight() / 2;

	float x = xPrime;
	float y = yPrime;

	if (xPrime < left)
		x = left;
	else if (xPrime > right)
		x = right;

	if (yPrime > up)
		y = up;
	else if (yPrime < down)
		y = down;

	return pCircle->getRadius() > MathUtility::distance(xPrime, yPrime, x, y);;
}

bool PhysicsCalc::isCollision2D(CircleCollider2D * pCircle, BoxCollider2D * pBox)
{
	return isCollision2D(pBox, pCircle);
}

void PhysicsCalc::fixPosition2D(CircleCollider2D * pCircle1, CircleCollider2D * pCircle2)
{
}

void PhysicsCalc::fixPosition2D(BoxCollider2D * pBox1, BoxCollider2D * pBox2)
{
	Vec3 box1Pos = pBox1->position();
	Vec3 box2Pos = pBox2->position();

	HitDirection hitDir = getHitDirection(pBox1, pBox2);

	Vec3 box2FixPos = box2Pos;

	float xDistance = (pBox1->getWidth() + pBox2->getWidth()) * 0.5f;
	float yDistance = (pBox1->getHeight() + pBox2->getHeight()) * 0.5f;

	//衝突した方向に応じて押し出し
	switch (hitDir)
	{
	case UP:
		box2FixPos.y = box1Pos.y + yDistance;
		break;
	case DOWN:
		box2FixPos.y = box1Pos.y - yDistance;
		break;
	case LEFT:
		box2FixPos.x = box1Pos.x - xDistance;
		break;
	case RIGHT:
		box2FixPos.x = box1Pos.x + xDistance;
		break;
	}

	pBox2->getUser()->setPosition(box2FixPos);
}

void PhysicsCalc::fixPosition2D(BoxCollider2D * pBox, CircleCollider2D * pCircle)
{
}

void PhysicsCalc::fixPosition2D(CircleCollider2D * pCircle, BoxCollider2D * pBox)
{
	fixPosition2D(pBox, pCircle);
}

bool PhysicsCalc::isIntersect3D(const Sphere3D & sphere1, const Sphere3D & sphere2)
{
	return false;
}

void PhysicsCalc::fixPosition3D(Sphere3D & sphere1, const Sphere3D & sphere2)
{
}
