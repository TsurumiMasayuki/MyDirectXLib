#include "Color.h"

Color::Color()
	: Color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Color::Color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{
}

Color::Color(DirectX::XMVECTOR color, float alpha)
	: Color(color.m128_f32[0], color.m128_f32[1], color.m128_f32[2], alpha)
{
}

Color::~Color()
{
}

DirectX::XMVECTOR Color::toXMVECTOR() const
{
	return { r, g, b, a };
}
