#pragma once
#include <DirectXMath.h>

struct D3D11_INPUT_ELEMENT_DESC;

struct MeshVertex
{
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Normal;
	DirectX::XMFLOAT2 m_UV;

	static void getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[3]);
};