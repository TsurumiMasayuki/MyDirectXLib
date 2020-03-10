#pragma once
#include <DirectXMath.h>

struct SpriteConstantBuffer
{
	SpriteConstantBuffer() 
		: uvOffset(0.0f, 0.0f),
		uvSize(1.0f, 1.0f),
		color(1.0f, 1.0f, 1.0f, 1.0f),
		pivot(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	DirectX::XMFLOAT4X4 wvpMatrix;
	DirectX::XMFLOAT2 uvOffset;
	DirectX::XMFLOAT2 uvSize;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 pivot;
};