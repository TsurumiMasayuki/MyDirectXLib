#pragma once
#include <DirectXMath.h>

struct Vec3;

struct Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	~Vec2();

	DirectX::XMVECTOR toXMVector() const;

	Vec2 normalized();
	float length() const;
	float sqrLength() const;
	float distance(const Vec2 & other) const;
	float sqrDistance(const Vec2 & other) const;

	float angle() const;
	float angleBetween(const Vec2 & other) const;

	Vec3 toVec3();

	static Vec2 zero();
	static Vec2 rotateBy(Vec2 rotatePos, Vec2 rotateOrigin, float degree);
	static Vec2 moveTowards(Vec2 origin, Vec2 destination, float ratio);
	static Vec2 angleToVec(float angle);
	static float dot(const Vec2& vec1, const Vec2& vec2);

#pragma region Operator

	Vec2 operator + (Vec2 other)
	{
		return Vec2(
			this->x + other.x,
			this->y + other.y
		);
	};

	Vec2 operator - (Vec2 other)
	{
		return Vec2(
			this->x - other.x,
			this->y - other.y
		);
	};

	Vec2 operator * (float n)
	{
		return Vec2(
			this->x * n,
			this->y * n
		);
	}

	Vec2 operator / (float n)
	{
		return Vec2(
			this->x / n,
			this->y / n
		);
	}

	Vec2& operator += (Vec2 other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vec2& operator -= (Vec2 other)
	{
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	Vec2& operator *= (float n)
	{
		this->x *= n;
		this->y *= n;

		return *this;
	}

	Vec2& operator /= (float n)
	{
		this->x /= n;
		this->y /= n;

		return *this;
	}

#pragma endregion

public:
	float x;
	float y;
};