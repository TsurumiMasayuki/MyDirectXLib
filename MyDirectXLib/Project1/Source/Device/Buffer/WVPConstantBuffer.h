#pragma once
#include <DirectXMath.h>

struct WVPConstantBuffer
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 viewProj;
	DirectX::XMFLOAT4X4 worldInv;
};