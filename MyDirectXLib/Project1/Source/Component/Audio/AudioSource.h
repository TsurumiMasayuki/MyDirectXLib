#pragma once
#include <string>
#include "Component\AbstractComponent.h"

class AudioInstance;

//音声再生用コンポーネント
class AudioSource
	: public AbstractComponent
{
public:
	AudioSource(GameObject* m_pUser);
	~AudioSource();

	virtual void onStart() override;
	virtual void onUpdate() override;

	//再生(ループ回数が255の場合無限ループ。途中から再生した場合は無視されます。)
	void play(int loopCount = 0);
	//再生停止
	void stop();
	//再生中断
	void pause();

	//音声を設定(ループ回数が255の場合無限ループ)
	void setAudio(std::string audioName, int loopCount = 0);

	//ボリューム設定(倍率)
	void setVolume(float volume);
	//ボリュームを取得
	float getVolume();

private:
	float m_Distance;					//音声が聞こえる範囲
	std::string m_AudioName;			//音声アセット名
	AudioInstance* m_pAudioInstance;	//音声再生補助
};