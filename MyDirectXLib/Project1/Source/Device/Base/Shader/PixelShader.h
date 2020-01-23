#pragma once

#include <d3d11.h>

class PixelShader
{
public:
	PixelShader(const char* filePath);
	~PixelShader();

	ID3D11PixelShader* getShader();

private:
	ID3D11PixelShader* m_pPixelShader;
};