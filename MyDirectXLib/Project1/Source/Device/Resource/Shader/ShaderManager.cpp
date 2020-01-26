#include "ShaderManager.h"
#include "Device\DirectXManager.h"
#include <unordered_map>
#include <d3d11.h>

#include "VertexShader.h"
#include "PixelShader.h"

using namespace std;

static unordered_map<string, VertexShader*> vsList;
static unordered_map<string, PixelShader*> psList;

HRESULT ShaderManager::LoadVertexShader_CSO(std::string key, const CHAR * filePath)
{
	auto pVertexShader = new VertexShader(filePath);
	vsList.emplace(key, pVertexShader);
	return S_OK;
}

HRESULT ShaderManager::LoadPixelShader_CSO(std::string key, const CHAR * filePath)
{
	auto pPixelShader = new PixelShader(filePath);
	psList.emplace(key, pPixelShader);
	return S_OK;
}

VertexShader * ShaderManager::GetVertexShader(const std::string key)
{
	return vsList.at(key);
}

PixelShader * ShaderManager::GetPixelShader(const std::string key)
{
	return psList.at(key);
}

ID3D11VertexShader * ShaderManager::GetVertexShaderInstance(const string key)
{
	return vsList.at(key)->getShader();
}

ID3D11PixelShader * ShaderManager::GetPixelShaderInstance(const string key)
{
	return psList.at(key)->getShader();
}

void ShaderManager::unLoadAll()
{
	for (auto shader : vsList)
	{
		delete shader.second;
	}
	vsList.clear();

	for (auto shader : psList)
	{
		delete shader.second;
	}
	psList.clear();
}
