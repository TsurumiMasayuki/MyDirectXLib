#pragma once
#include <DirectXMath.h>

struct SpriteConstantBuffer
{
	DirectX::XMFLOAT4X4 wvpMatrix;
	DirectX::XMFLOAT2 uvOffset;
	DirectX::XMFLOAT2 uvSize;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 pivot;
};