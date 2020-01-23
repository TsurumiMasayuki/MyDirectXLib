#include "Vec2.h"
#include "Vec3.h"
#include "Math\MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace DirectX;

Vec2::Vec2()
	: x(0), y(0)
{
}

Vec2::Vec2(float x, float y)
	: x(x), y(y)
{
}

Vec2::~Vec2()
{
}

DirectX::XMVECTOR Vec2::toXMVector() const
{
	XMVECTOR xmVector = XMVECTOR();
	xmVector.m128_f32[0] = x;
	xmVector.m128_f32[1] = y;
	return xmVector;
}

Vec2 Vec2::normalized()
{
	float length = this->length();
	if (length == 0) return Vec2::zero();

	return *this / this->length();
}

float Vec2::length() const
{
	XMVECTOR result = XMVector2Length(this->toXMVector());
	return result.m128_f32[0];
}

float Vec2::sqrLength() const
{
	XMVECTOR result = XMVector2LengthSq(this->toXMVector());
	return result.m128_f32[0];
}

float Vec2::distance(const Vec2 & other) const
{
	Vec2 vec1 = *this;
	Vec2 diff = vec1 - other;
	return diff.length();
}

float Vec2::sqrDistance(const Vec2 & other) const
{
	Vec2 vec1 = *this;
	Vec2 diff = vec1 - other;
	return diff.sqrLength();
}

float Vec2::angle() const
{
	return atan2f(y, x);
}

float Vec2::angleBetween(const Vec2 & other) const
{
	XMVECTOR result = XMVector2AngleBetweenVectors(this->toXMVector(), other.toXMVector());
	return result.m128_f32[0];
}

Vec3 Vec2::toVec3()
{
	return Vec3(x, y, 0);
}

Vec2 Vec2::zero()
{
	return Vec2(0, 0);
}

Vec2 Vec2::rotateBy(Vec2 rotatePos, Vec2 rotateOrigin, float degree)
{
	Vec2 rotate;
	Vec2 diff = rotatePos - rotateOrigin;
	float angle = MathUtility::toRadian(degree);

	float sin = sinf(angle);
	float cos = cosf(angle);

	rotate.x = diff.x * cos - diff.y * sin + rotateOrigin.x;
	rotate.y = diff.x * sin + diff.y * cos + rotateOrigin.y;

	return rotate;
}

Vec2 Vec2::moveTowards(Vec2 origin, Vec2 destination, float ratio)
{
	return origin + (destination - origin) * ratio;
}

Vec2 Vec2::angleToVec(float angle)
{
	float radian = angle * (M_PI / 180);
	return Vec2(cos(radian), sin(radian));
}

float Vec2::dot(const Vec2 & vec1, const Vec2 & vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}
