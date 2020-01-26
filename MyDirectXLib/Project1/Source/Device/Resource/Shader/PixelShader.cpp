#include "PixelShader.h"
#include <cstdio>
#include "Device\DirectXManager.h"

#ifdef _DEBUG
#include <cassert>
#endif

PixelShader::PixelShader(const char * filePath)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, filePath, "rb");	//バイト読み込みモードにする

#ifdef _DEBUG
	assert(pFile != nullptr);
#endif

	fseek(pFile, 0, SEEK_END); 		//ファイル末尾まで移動
	long fileSize = ftell(pFile);	//現在の位置(↑で移動したので末尾)を取得
	fseek(pFile, 0, SEEK_SET);		//ファイルの先頭に移動

	unsigned char* fileData = new unsigned char[fileSize];	//データ格納用配列を作成
	fread(fileData, fileSize, 1, pFile);					//ファイルデータを読み込み
	fclose(pFile);											//読み込みが終わったのでファイルを閉じる

	auto pDevice = DirectXManager::getDevice();

	pDevice->CreatePixelShader(fileData, fileSize, NULL, &m_pPixelShader);

	delete[] fileData;
}

PixelShader::~PixelShader()
{
	m_pPixelShader->Release();
}

ID3D11PixelShader * PixelShader::getShader()
{
	return m_pPixelShader;
}
