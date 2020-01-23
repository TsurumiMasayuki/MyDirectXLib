#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include <stdlib.h>
#include <sstream>

#include <chrono>

#include "WindowInstance.h"
#include "Device\ShaderManager.h"
#include "Device\DirectXManager.h"
#include "Device\SoundManager.h"
#include "Device\GameTime.h"

#include "Game.h"

WindowInstance* g_pWindowInstance;
Game* g_pGame;

#define MIN_FRAME_TIME 1.0f / 60.0f

void app()
{
	GameTime::update();

	float unscaledDeltaTime = GameTime::getUnscaledDeltaTime();
	if (unscaledDeltaTime < MIN_FRAME_TIME)
	{
		float diff = MIN_FRAME_TIME - unscaledDeltaTime;
		GameTime::addSleepTime(diff);
		Sleep(diff * 1000.0f);
	}

	g_pGame->update();
	g_pGame->draw();
}

HRESULT initDX()
{
	ID3D11Device* pDevice = DirectXManager::getDevice();
	ID3D11DeviceContext* pDeviceContext = DirectXManager::getDeviceContext();

	//バーテックスシェーダ作成
	ShaderManager::LoadVertexShader_CSO("SpriteDefault", "Assets/Shaders/SpriteVS.cso");

	//ピクセルシェーダ作成
	ShaderManager::LoadPixelShader_CSO("SpriteDefault", "Assets/Shaders/SpritePS.cso");

	return S_OK;
}

#pragma region XAudio2

IXAudio2* g_pXAudio2;
IXAudio2MasteringVoice* g_pMasteringVoice;

void initXAudio()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	UINT32 flags = 0;
#if defined(_DEBUG)
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif
	XAudio2Create(&g_pXAudio2, flags);

	g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);

	SoundManager::initialize(g_pXAudio2, g_pMasteringVoice);
}

void shutdownXAudio()
{
	SoundManager::shutdown();
	g_pMasteringVoice->DestroyVoice();
	g_pXAudio2->Release();
	g_pXAudio2 = nullptr;
	CoUninitialize();
}

#pragma endregion

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ INT nCmdShow)
{
	g_pWindowInstance = new WindowInstance(&hInstance, "Project1", 0, 0);
	g_pWindowInstance->show(SW_SHOW);
	g_pWindowInstance->update();
	g_pWindowInstance->adjustWindowSize();

	DirectXManager::initialize(g_pWindowInstance->getHWND());

	if (FAILED(initDX())) return 1;
	initXAudio();

	MSG msg = { 0 };

	g_pGame = new Game();
	g_pGame->init();

	while (msg.message != WM_QUIT)
	{
		BOOL msgFlag = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msgFlag)
			DispatchMessage(&msg);
		else
			app();
	}

	g_pGame->shutdown();
	delete(g_pGame);

	ShaderManager::releaseAll();
	DirectXManager::shutdown();
	shutdownXAudio();

	delete(g_pWindowInstance);

	return 0;
}