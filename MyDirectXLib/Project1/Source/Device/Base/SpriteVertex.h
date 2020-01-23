#pragma once
#include <DirectXMath.h>

struct D3D11_INPUT_ELEMENT_DESC;

class SpriteVertex
{
public:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT2 m_TexCoord;

	static void getInputDesc(D3D11_INPUT_ELEMENT_DESC layoutArray[2]);
};