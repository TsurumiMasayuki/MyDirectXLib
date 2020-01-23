#pragma once
#include <d3d11.h>

#include "Device\Base\Shader\VertexShader.h"
#include "Device\Base\Shader\PixelShader.h"

#include <string>

class ShaderManager
{
public:
	//static HRESULT LoadVertexShader(
	//	ID3D11Device * pDevice,
	//	const std::string key,
	//	const void * pShaderByteCode,
	//	SIZE_T byteCodeLength);

	//static HRESULT LoadPixelShader(
	//	ID3D11Device * pDevice,
	//	const std::string key,
	//	const void * pShaderByteCode,
	//	SIZE_T byteCodeLength);

	static HRESULT LoadVertexShader_CSO(std::string key, const CHAR* filePath);
	static HRESULT LoadPixelShader_CSO(std::string key, const CHAR* filePath);

	static VertexShader* GetVertexShader(const std::string key);
	static PixelShader* GetPixelShader(const std::string key);

	static ID3D11VertexShader* GetVertexShaderInstance(const std::string key);
	static ID3D11PixelShader* GetPixelShaderInstance(const std::string key);

	static void releaseAll();

private:
	ShaderManager() {};
	~ShaderManager() {};

};

