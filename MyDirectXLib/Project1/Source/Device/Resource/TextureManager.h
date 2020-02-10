#pragma once
#include <d3d11.h>
#include <string>

class TextureManager
{
public:
	static HRESULT loadTexture(const WCHAR* filePath, std::string key);
	static ID3D11Resource * getTexture(std::string key);
	static ID3D11ShaderResourceView * getTextureView(std::string key);

	static void unLoadTexture(std::string key);
	static void unLoadAll();

private:
	TextureManager() {};
	~TextureManager() {};
};

