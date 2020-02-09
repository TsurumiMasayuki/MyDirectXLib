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

	const Vec3 normalized() const;
	float length() const;
	float sqrLength() const;
	float distance(const Vec3 & other) const;
	float sqrDistance(const Vec3 & other) const;

	static Vec3 zero();
	//fromからtoまでtの分移動した位置ベクトルを返します
	static Vec3 moveTowards(const Vec3& from, const Vec3& to, float t);

	Vec2 toVec2();

#pragma region Operator

	const Vec3 operator + (const Vec3& other) const
	{
		return Vec3(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
		);
	};

	const Vec3 operator - (const Vec3& other) const
	{
		return Vec3(
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		);
	};

	const Vec3 operator * (float n) const
	{
		return Vec3(
			this->x * n,
			this->y * n,
			this->z * n
		);
	}

	const Vec3 operator / (float n) const
	{
		return Vec3(
			this->x / n,
			this->y / n,
			this->z / n
		);
	}

	Vec3& operator += (const Vec3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	Vec3& operator -= (const Vec3& other)
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

