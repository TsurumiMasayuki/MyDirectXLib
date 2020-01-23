#include "SoundInstance.h"

SoundInstance::SoundInstance(IXAudio2SourceVoice * pSourceVoice)
	:m_pSourceVoice(pSourceVoice)
{
}

SoundInstance::~SoundInstance()
{
}

void SoundInstance::start()
{
	m_pSourceVoice->Start();
}

void SoundInstance::shutdown()
{
	m_pSourceVoice->DestroyVoice();
}

bool SoundInstance::isEnd()
{
	XAUDIO2_VOICE_STATE voiceState;
	m_pSourceVoice->GetState(&voiceState);

	return voiceState.BuffersQueued == 0;
}
