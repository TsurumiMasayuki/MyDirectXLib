#pragma once
#include <DirectXMath.h>

struct D3D11_INPUT_ELEMENT_DESC;

struct MeshVertex
{
	DirectX::XMFLOAT4 m_Pos;
	DirectX::XMFLOAT4 m_Normal;

	static void getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[2]);
};