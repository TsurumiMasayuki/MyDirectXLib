#include "Game.h"
#include <Windows.h>

#include "Scene\SceneManager.h"
#include "Scene\TestScene.h"

#include "Device\GameDevice.h"
#include "Device\Renderer.h"

#include "Device\Resource\TextureManager.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\MeshManager.h"
#include "Device\Resource\AudioManager.h"

#include <DirectXColors.h>
#include "Device\Camera.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");
	TextureManager::loadTexture(L"Assets/Textures/Default.png", "Default");
	TextureManager::loadTexture(L"Assets/Textures/MetaBall.png", "MetaBall");

	//スプライト用シェーダーを読み込み
	ShaderManager::LoadVertexShader_CSO("SpriteVS", "Assets/Shaders/SpriteVS.cso");
	ShaderManager::LoadPixelShader_CSO("SpritePS", "Assets/Shaders/SpritePS.cso");

	//3Dモデル用シェーダーを読み込み
	ShaderManager::LoadVertexShader_CSO("MeshVS", "Assets/Shaders/MeshVS.cso");
	ShaderManager::LoadPixelShader_CSO("MeshPS", "Assets/Shaders/MeshPS.cso");

	ShaderManager::LoadPixelShader_CSO("BlurPS", "Assets/Shaders/BlurPS.cso");
	ShaderManager::LoadPixelShader_CSO("MetaBallPS", "Assets/Shaders/MetaBallPS.cso");

	ShaderManager::LoadVertexShader_CSO("BasicVS", "Assets/Shaders/BasicVS.cso");
	ShaderManager::LoadPixelShader_CSO("BasicPS", "Assets/Shaders/BasicPS.cso");

	ShaderManager::LoadPixelShader_CSO("CircleFillPS", "Assets/Shaders/WaterFallGame/CircleFillPS.cso");
	ShaderManager::LoadPixelShader_CSO("CircleGradPS", "Assets/Shaders/WaterFallGame/CircleGradPS.cso");
	ShaderManager::LoadPixelShader_CSO("SplashPS", "Assets/Shaders/WaterFallGame/SplashPS.cso");

	GameDevice::initialize();
	GameDevice::getMeshManager()->loadMesh("Vox", "Assets/Models/testVox.fbx", L"Assets/Models/testVox.png");
	GameDevice::getMeshManager()->loadMesh("TestMesh", "Assets/Models/tekitou.fbx");
	GameDevice::getMeshManager()->loadMesh("Cube", "Assets/Models/cube.fbx");
	GameDevice::getMeshManager()->loadMesh("Sphere", "Assets/Models/sphere.fbx");

	GameDevice::getAudioManager()->loadWavFile("MusicMono", L"Assets/Sounds/MusicMono.wav");

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Test", new TestScene());
	m_pSceneManager->changeScene("Test");
}

void Game::update()
{
	GameDevice::update();

	//シーンの更新
	m_pSceneManager->update();
}

void Game::draw()
{
	GameDevice::getRenderer()->draw();
}

void Game::shutdown()
{
	delete m_pSceneManager;

	TextureManager::unLoadAll();
	ShaderManager::unLoadAll();
	GameDevice::shutdown();
}
