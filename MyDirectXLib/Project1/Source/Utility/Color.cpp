#include "Color.h"

Color::Color()
	: Color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Color::Color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{
}

Color::Color(DirectX::XMVECTOR color)
	: Color(color.m128_f32[0], color.m128_f32[1], color.m128_f32[2], color.m128_f32[3])
{
}

Color::~Color()
{
}

DirectX::XMVECTOR Color::toXMFLOAT4() const
{
	return { r, g, b, a };
}
