#pragma once
#include <xaudio2.h>

struct SoundInstance
{
public:
	SoundInstance(IXAudio2SourceVoice* pSourceVoice);
	~SoundInstance();

	void start();
	void shutdown();
	bool isEnd();

private:
	IXAudio2SourceVoice* m_pSourceVoice;
};

