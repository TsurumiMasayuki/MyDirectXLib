#pragma once
#include <d3d11.h>

class VertexShader
{
public:
	VertexShader(const char* filePath);
	~VertexShader();

	ID3D11VertexShader* getShader();

	HRESULT createInputLayout(
		ID3D11Device* pDevice,
		D3D11_INPUT_ELEMENT_DESC* pInputDesc,
		UINT numElements,
		ID3D11InputLayout** ppInputLayout);

public:
	ID3D11VertexShader* m_pVertexShader;
	unsigned char* m_pShaderByteCode;
	SIZE_T m_ByteCodeLength;
};