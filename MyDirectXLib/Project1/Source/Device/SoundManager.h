#pragma once

#include <xaudio2.h>
#pragma comment(lib, "xaudio2.lib")

#include <vector>
#include <unordered_map>

#include "SoundInstance.h"
#include "WAVFileReader.h"

#include <string>

class SoundManager
{
public:
	static void initialize(IXAudio2* pXAudio2, IXAudio2MasteringVoice* pMasteringVoice);
	static void update();
	static void shutdown();

	static void loadWavFile(const WCHAR* filePath , std::string key);
	static void playSE(std::string key, UINT loopCount = 0);
	static void playBGM(std::string key);
	static void stopBGM();

private:
	SoundManager(IXAudio2* pXAudio2, IXAudio2MasteringVoice* pMasteringVoice);
	~SoundManager();

private:
	static SoundManager* pInstance;

	IXAudio2* m_pXAudio2;
	IXAudio2MasteringVoice* m_pMasteringVoice;

	SoundInstance* m_pBGMInstance;

	std::unordered_map<std::string, DirectX::WAVData> mWavData;
	std::unordered_map<std::string, std::unique_ptr<uint8_t[]>> mFileData;
	std::vector<SoundInstance*> mSoundInstances;
};