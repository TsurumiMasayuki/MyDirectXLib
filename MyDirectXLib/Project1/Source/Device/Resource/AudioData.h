#pragma once
#include <string>
#include <memory>

namespace DirectX
{
	struct WAVData;
}

//音声データ保持用
class AudioData
{
public:
	AudioData();
	~AudioData();

	//初期化(読み込み)
	void init(const std::wstring filePath);
	//WAVDataの取得
	const DirectX::WAVData& getWAVData() const;
	
private:
	DirectX::WAVData* m_pWAVData;					//再生用データ
	std::unique_ptr<uint8_t[]> m_pFileDataArray;	//音声データ(本体)
};