#include "Game.h"
#include <Windows.h>

#include "Scene\SceneManager.h"
#include "Scene\TestScene.h"

#include "Device\GameDevice.h"
#include "Device\Renderer.h"

#include "Device\Resource\TextureManager.h"
#include "Device\Resource\SoundManager.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\MeshManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
#ifdef _DEBUG
	//デバッグ時ならメモリ追跡用オプションをオンにする
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

	TextureManager::loadTexture(L"Assets/Textures/CircleFill.png", "CircleFill");
	TextureManager::loadTexture(L"Assets/Textures/CircleOutline.png", "CircleOutline");
	TextureManager::loadTexture(L"Assets/Textures/BoxFill.png", "BoxFill");
	TextureManager::loadTexture(L"Assets/Textures/BoxOutline.png", "BoxOutline");

	//スプライト用シェーダーを読み込み
	ShaderManager::LoadVertexShader_CSO("SpriteVS", "Assets/Shaders/SpriteVS.cso");
	ShaderManager::LoadPixelShader_CSO("SpritePS", "Assets/Shaders/SpritePS.cso");

	//3Dモデル用シェーダーを読み込み
	ShaderManager::LoadVertexShader_CSO("MeshVS", "Assets/Shaders/MeshVS.cso");
	ShaderManager::LoadPixelShader_CSO("MeshPS", "Assets/Shaders/MeshPS.cso");

	GameDevice::initialize();
	GameDevice::getMeshManager()->loadMesh("TestMesh", "Assets/Models/tekitou.fbx");
	GameDevice::getMeshManager()->loadMesh("Cube", "Assets/Models/cube.fbx");

	m_pSceneManager = new SceneManager();
	m_pSceneManager->addScene("Test", new TestScene());
	m_pSceneManager->changeScene("Test");
}

void Game::update()
{
	GameDevice::update();

	SoundManager::update();

	//シーンの更新
	m_pSceneManager->update();
}

void Game::draw()
{
	m_pSceneManager->draw();

	GameDevice::getRenderer()->draw();
}

void Game::shutdown()
{
	delete m_pSceneManager;

	TextureManager::unLoadAll();
	ShaderManager::unLoadAll();
	GameDevice::shutdown();
}
