#include "SoundManager.h"
#include "WAVFileReader.cpp"
#include "Def\ManagerConfig.h"

using namespace std;
using namespace DirectX;

SoundManager* SoundManager::pInstance = nullptr;

void SoundManager::initialize(IXAudio2 * pXAudio2, IXAudio2MasteringVoice* pMasteringVoice)
{
	if (pInstance == nullptr)
		pInstance = new SoundManager(pXAudio2, pMasteringVoice);

	pInstance->mSoundInstances.reserve(ManagerConfig::SoundInstanceReserve);
}

void SoundManager::update()
{
	auto itr = pInstance->mSoundInstances.begin();
	while (itr != pInstance->mSoundInstances.end())
	{
		if ((*itr)->isEnd())
		{
			(*itr)->shutdown();
			delete (*itr);
			itr = pInstance->mSoundInstances.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void SoundManager::shutdown()
{
	if (pInstance != nullptr)
		delete pInstance;
	pInstance = nullptr;
}

void SoundManager::loadWavFile(const WCHAR* filePath, std::string key)
{
	WAVData wavData;
	unique_ptr<uint8_t[]> fileData;

	if (FAILED(LoadWAVAudioFromFileEx(filePath, fileData, wavData)))
	{
		pInstance->shutdown();
	}

	pInstance->mWavData.emplace(key, wavData);
	pInstance->mFileData.emplace(key, move(fileData));
}

void SoundManager::playSE(std::string key, UINT loopCount)
{
	WAVData waveData = pInstance->mWavData.at(key);
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	if (FAILED(pInstance->m_pXAudio2->CreateSourceVoice(&pSourceVoice, waveData.wfx)))
	{
		pInstance->shutdown();
	}
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = waveData.startAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = waveData.audioBytes;
	buffer.LoopCount = loopCount;

	pSourceVoice->SubmitSourceBuffer(&buffer);

	auto pSoundInstance = new SoundInstance(pSourceVoice);
	pInstance->mSoundInstances.emplace_back(pSoundInstance);
	pSoundInstance->start();
}

void SoundManager::playBGM(std::string key)
{
	if (pInstance->m_pBGMInstance != nullptr)
	{
		stopBGM();
	}

	WAVData waveData = pInstance->mWavData.at(key);
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	if (FAILED(pInstance->m_pXAudio2->CreateSourceVoice(&pSourceVoice, waveData.wfx)))
	{
		pInstance->shutdown();
	}
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = waveData.startAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = waveData.audioBytes;
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	pSourceVoice->SubmitSourceBuffer(&buffer);
	pInstance->m_pBGMInstance = new SoundInstance(pSourceVoice);
	pInstance->m_pBGMInstance->start();
}

void SoundManager::stopBGM()
{
	if (pInstance->m_pBGMInstance == nullptr) return;
	pInstance->m_pBGMInstance->shutdown();
	delete pInstance->m_pBGMInstance;
	pInstance->m_pBGMInstance = nullptr;
}

SoundManager::SoundManager(IXAudio2* pXaudio2, IXAudio2MasteringVoice* pMasteringVoice)
	:m_pXAudio2(pXaudio2), m_pMasteringVoice(pMasteringVoice)
{

}

SoundManager::~SoundManager()
{
	if (m_pBGMInstance != nullptr)
	{
		m_pBGMInstance->shutdown();
		delete m_pBGMInstance;
	}

	for (auto& pSoundInstance : mSoundInstances)
	{
		pSoundInstance->shutdown();
	}

	mSoundInstances.clear();
}
