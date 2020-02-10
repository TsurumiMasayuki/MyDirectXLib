#pragma once

class Renderer;
class MeshManager;
class AudioManager;

class GameDevice
{
public:
	static void initialize();
	static void update();
	static void shutdown();

	static Renderer* getRenderer();
	static MeshManager* getMeshManager();
	static AudioManager* getAudioManager();

private:
	GameDevice();
	~GameDevice();

	//ÉRÉsÅ[ã÷é~
	GameDevice(const GameDevice& other) = delete;
	GameDevice& operator = (const GameDevice& other) = delete;

private:
	static GameDevice* instance;

	Renderer* m_pRenderer;
	MeshManager* m_pMeshManager;
	AudioManager* m_pAudioManager;
};