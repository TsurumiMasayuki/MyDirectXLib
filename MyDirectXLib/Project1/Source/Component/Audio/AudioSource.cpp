#include "AudioSource.h"
#include "Device\GameDevice.h"
#include "Device\Resource\AudioManager.h"
#include "Device\Resource\AudioInstance.h"

AudioSource::AudioSource(GameObject * m_pUser)
	: AbstractComponent(m_pUser),
	m_Distance(0.0f),
	m_pAudioInstance(nullptr),
	m_AudioName("")
{
}

AudioSource::~AudioSource()
{
	if (m_pAudioInstance != nullptr)
		delete m_pAudioInstance;
}

void AudioSource::onStart()
{
}

void AudioSource::onUpdate()
{

}

void AudioSource::play(int loopCount)
{
	//音声が設定されていなかったらreturn
	if (m_pAudioInstance == nullptr ||
		m_AudioName.empty()) return;

	if (m_pAudioInstance->isEnd())
		//再生が終わっていたら新しく再生
		setAudio(m_AudioName, loopCount);
	else
		//そうでない場合は途中から
		m_pAudioInstance->start();
}

void AudioSource::stop()
{
	//音声が設定されていなかったらreturn
	if (m_pAudioInstance == nullptr) return;

	delete m_pAudioInstance;
	m_pAudioInstance = nullptr;
}

void AudioSource::pause()
{
	//音声が設定されていなかったらreturn
	if (m_pAudioInstance == nullptr) return;

	m_pAudioInstance->pause();
}

void AudioSource::setAudio(std::string audioName, int loopCount)
{
	m_AudioName = audioName;

	//音声が再生中の場合ストップ
	if (m_pAudioInstance != nullptr)
	{
		m_pAudioInstance->stop();
		delete m_pAudioInstance;
	}

	//音声を設定
	m_pAudioInstance =
		new AudioInstance(
			GameDevice::getAudioManager()->getXAudio2(),
			GameDevice::getAudioManager()->getAudioData(audioName),
			loopCount
		);
}

void AudioSource::setVolume(float volume)
{
	//音声が設定されていなかったらreturn
	if (m_pAudioInstance == nullptr) return;

	m_pAudioInstance->setVolume(volume);
}

float AudioSource::getVolume()
{
	//音声が設定されていなかったらreturn
	if (m_pAudioInstance == nullptr) return 0.0f;

	return m_pAudioInstance->getVolume();
}
