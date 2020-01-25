#pragma once
#include <DirectXMath.h>

struct D3D11_INPUT_ELEMENT_DESC;

struct ModelVertex
{
	DirectX::XMFLOAT4 m_Pos;

	//static void getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[2]);
};