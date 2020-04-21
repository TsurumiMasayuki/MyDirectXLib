#pragma once
#include <DirectXMath.h>
#include <DirectXColors.h>

struct Color
{
public:
	Color();
	Color(float r, float g, float b, float a);
	//DirectX::Colors—p
	Color(DirectX::XMVECTOR color, float alpha = 1.0f);
	~Color();

	DirectX::XMVECTOR toXMVECTOR() const;

public:
	float r;
	float g;
	float b;
	float a;
};