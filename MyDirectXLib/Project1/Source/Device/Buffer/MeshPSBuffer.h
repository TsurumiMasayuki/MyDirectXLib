#pragma once
#include <DirectXMath.h>

struct MeshPSBuffer
{
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT4 lightPos;
	DirectX::XMFLOAT4 lightAttenuation;
	DirectX::XMFLOAT4 lightColor;
};