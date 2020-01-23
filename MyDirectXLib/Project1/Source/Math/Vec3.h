#pragma once
#include <DirectXMath.h>

struct Vec2;

struct Vec3
{
public:
	Vec3();
	Vec3(float x, float y, float z);
	~Vec3();

	DirectX::XMVECTOR toXMVector() const;

	Vec3 normalized();
	float length() const;
	float sqrLength() const;
	float distance(const Vec3 & other) const;
	float sqrDistance(const Vec3 & other) const;

	static Vec3 zero();

	Vec2 toVec2();

#pragma region Operator

	Vec3 operator + (Vec3 other)
	{
		return Vec3(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
		);
	};

	Vec3 operator - (Vec3 other)
	{
		return Vec3(
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		);
	};

	Vec3 operator * (float n)
	{
		return Vec3(
			this->x * n,
			this->y * n,
			this->z * n
		);
	}

	Vec3 operator / (float n)
	{
		return Vec3(
			this->x / n,
			this->y / n,
			this->z / n
		);
	}

	Vec3& operator += (Vec3 other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	Vec3& operator -= (Vec3 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	Vec3& operator *= (float n)
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;

		return *this;
	}

	Vec3& operator /= (float n)
	{
		this->x /= n;
		this->y /= n;
		this->z /= n;

		return *this;
	}

#pragma endregion

public:
	float x;
	float y;
	float z;
};

