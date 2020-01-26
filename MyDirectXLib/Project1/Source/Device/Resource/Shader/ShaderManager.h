#pragma once
#include <d3d11.h>
#include <string>

class VertexShader;
class PixelShader;

struct ID3D11VertexShader;
struct ID3D11PixelShader;

class ShaderManager
{
public:
	static HRESULT LoadVertexShader_CSO(std::string key, const CHAR* filePath);
	static HRESULT LoadPixelShader_CSO(std::string key, const CHAR* filePath);

	static VertexShader* GetVertexShader(const std::string key);
	static PixelShader* GetPixelShader(const std::string key);

	static ID3D11VertexShader* GetVertexShaderInstance(const std::string key);
	static ID3D11PixelShader* GetPixelShaderInstance(const std::string key);

	static void unLoadAll();

private:
	ShaderManager() {};
	~ShaderManager() {};

};

