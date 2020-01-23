#include "Game.h"
#include <Windows.h>

#include "Scene\SceneManager.h"

#include "Device\GameDevice.h"
#include "Device\Renderer.h"

#include "Device\TextureManager.h"
#include "Device\SoundManager.h"

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

	GameDevice::initialize();

	m_pSceneManager = new SceneManager();
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
	GameDevice::shutdown();
}
