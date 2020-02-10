#include "AudioData.h"
#include "WAVFileReader.h"
#include "WAVFileReader.cpp"

AudioData::AudioData()
	: m_pWAVData(new DirectX::WAVData())
{
}

AudioData::~AudioData()
{
	delete m_pWAVData;
}

void AudioData::init(const std::wstring filePath)
{
	//ÉtÉ@ÉCÉãÇ©ÇÁì«Ç›çûÇ›
	DirectX::LoadWAVAudioFromFileEx(filePath.c_str(), m_pFileDataArray, *m_pWAVData);
}

const DirectX::WAVData & AudioData::getWAVData() const
{
	return *m_pWAVData;
}
