#include "TextureManager.h"
#include <unordered_map>
#include "WICTextureLoader.h"
#include "WICTextureLoader.cpp"
#include "DirectXManager.h"
#include <stdlib.h>

using namespace std;

static unordered_map<string, ID3D11Resource*> textureList;
static unordered_map<string, ID3D11ShaderResourceView*> textureViewList;

HRESULT TextureManager::loadTexture(const WCHAR * filePath, std::string key)
{
	ID3D11Resource* pTexture;
	ID3D11ShaderResourceView* pTextureView;

	auto pDevice = DirectXManager::getDevice();
	HRESULT result = CreateWICTextureFromFile(pDevice, filePath, &pTexture, &pTextureView);

	textureList.emplace(key, pTexture);
	textureViewList.emplace(key, pTextureView);

	if (FAILED(result)) return E_FAIL;

	return S_OK;
}

ID3D11Resource * TextureManager::getTexture(std::string key)
{
	return textureList.at(key);
}

ID3D11ShaderResourceView * TextureManager::getTextureView(std::string key)
{
	return textureViewList.at(key);
}

void TextureManager::unLoadTexture(std::string key)
{
	ID3D11Resource* pResource = getTexture(key);
	textureList.erase(key);
	pResource->Release();
}

void TextureManager::unLoadAll()
{
	for (auto pResource : textureList)
	{
		pResource.second->Release();
	}
	textureList.clear();

	for (auto pResourceView : textureViewList)
	{
		pResourceView.second->Release();
	}
	textureViewList.clear();
}
