#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "WindowInstance.h"
#include "Device\DirectXManager.h"
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
		Sleep(diff * 1000.0f);
	}

	g_pGame->update();
	g_pGame->draw();
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ INT nCmdShow)
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

#ifdef _DEBUG
	//デバッグ時ならメモリ追跡用オプションをオンにする
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

	g_pWindowInstance = new WindowInstance(&hInstance, "Project1", 0, 0);
	g_pWindowInstance->show(SW_SHOW);
	g_pWindowInstance->update();
	g_pWindowInstance->adjustWindowSize();

	DirectXManager::initialize(g_pWindowInstance->getHWND());

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

	DirectXManager::shutdown();

	delete(g_pWindowInstance);

	CoUninitialize();

	return 0;
}