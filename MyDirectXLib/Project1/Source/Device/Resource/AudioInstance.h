#pragma once
class AudioData;
struct IXAudio2;
struct IXAudio2SourceVoice;

//SourceVoice再生補助
class AudioInstance
{
public:
	//loopCount = 255なら無限ループします。
	AudioInstance(IXAudio2* pXAudio2, const AudioData& data, unsigned int loopCount = 0);
	~AudioInstance();

	//再生
	void start();
	//再生停止
	void stop();
	//再生中止
	void pause();
	//ループを中止(最後まで再生されます)
	void stopLoop();

	//再生終了しているかどうか
	bool isEnd();

	//ボリューム設定(倍率)
	void setVolume(float volume);
	//ボリュームを取得
	float getVolume();

private:
	IXAudio2SourceVoice* m_pSourceVoice;
};