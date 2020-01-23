#include "VertexShader.h"
#include <cstdio>
#include "Device\DirectXManager.h"

VertexShader::VertexShader(const char* filePath)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, filePath, "rb");	//バイト読み込みモードにする

	fseek(pFile, 0, SEEK_END); 		//ファイル末尾まで移動
	long fileSize = ftell(pFile);	//現在の位置(↑で移動したので末尾)を取得
	fseek(pFile, 0, SEEK_SET);		//ファイルの先頭に移動

	m_pShaderByteCode = new unsigned char[fileSize];//データ格納用配列を作成
	fread(m_pShaderByteCode, fileSize, 1, pFile);					//ファイルデータを読み込み
	fclose(pFile);											//読み込みが終わったのでファイルを閉じる

	auto pDevice = DirectXManager::getDevice();

	pDevice->CreateVertexShader(m_pShaderByteCode, fileSize, NULL, &m_pVertexShader);
	m_ByteCodeLength = fileSize;
}

VertexShader::~VertexShader()
{
	m_pVertexShader->Release();
	delete[] m_pShaderByteCode;
}

ID3D11VertexShader * VertexShader::getShader()
{
	return m_pVertexShader;
}

HRESULT VertexShader::createInputLayout(ID3D11Device * pDevice, D3D11_INPUT_ELEMENT_DESC * pInputDesc, UINT numElements, ID3D11InputLayout ** ppInputLayout)
{
	return pDevice->CreateInputLayout(pInputDesc, numElements, m_pShaderByteCode, m_ByteCodeLength, ppInputLayout);
}
