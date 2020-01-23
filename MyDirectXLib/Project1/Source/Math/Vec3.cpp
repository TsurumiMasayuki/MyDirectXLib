#include "Vec3.h"
#include "Vec2.h"

using namespace DirectX;

Vec3::Vec3()
	:Vec3(0.0f, 0.0f, 0.0f)
{
}

Vec3::Vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vec3::~Vec3()
{
}

XMVECTOR Vec3::toXMVector() const
{
	XMVECTOR xmVector = XMVECTOR();
	xmVector.m128_f32[0] = x;
	xmVector.m128_f32[1] = y;
	xmVector.m128_f32[2] = z;
	return xmVector;
}

Vec3 Vec3::normalized()
{
	float length = this->length();
	if (length == 0) return Vec3::zero();

	return *this / this->length();
}

float Vec3::length()const
{
	XMVECTOR result = XMVector3Length(this->toXMVector());
	return result.m128_f32[0];
}

float Vec3::sqrLength()const
{
	XMVECTOR result = XMVector3LengthSq(this->toXMVector());
	return result.m128_f32[0];
}

float Vec3::distance(const Vec3 & other)const
{
	Vec3 vec1 = *this;
	Vec3 diff = vec1 - other;
	return diff.length();
}

float Vec3::sqrDistance(const Vec3 & other) const
{
	Vec3 vec1 = *this;
	Vec3 diff = vec1 - other;
	return diff.sqrLength();
}

Vec3 Vec3::zero()
{
	return Vec3(0.0f, 0.0f, 0.0f);
}

Vec2 Vec3::toVec2()
{
	return Vec2(x, y);
}
