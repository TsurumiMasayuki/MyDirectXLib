#pragma once
#include <string>
#include <unordered_map>

class AudioData;
struct IXAudio2;
struct IXAudio2MasteringVoice;

//âπê∫ånä«óù
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	IXAudio2* getXAudio2() const;
	IXAudio2MasteringVoice* getMasteringVoice() const;

	void loadWavFile(std::string key, std::wstring filePath);
	const AudioData& getAudioData(std::string key) const;

private:
	//âπê∫ÉfÅ[É^
	std::unordered_map<std::string, AudioData*> m_AudioDataList;
	//Xaudio2
	IXAudio2* m_pXAudio2;
	//MasteringVoice
	IXAudio2MasteringVoice* m_pMasteringVoice;
};