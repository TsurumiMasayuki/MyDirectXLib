#include "WindowInstance.h"
#include "Def\Screen.h"

WindowInstance* WindowInstance::pInstance = nullptr;

LRESULT DefWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}

WindowInstance::WindowInstance(
	HINSTANCE * phInstance,
	LPCSTR windowName,
	int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;

	m_Width = Screen::getWindowWidth();
	m_Height = Screen::getWindowHeight();

	WNDCLASSEX wex = { 0 };
	wex.cbSize = sizeof(WNDCLASSEX);
	wex.lpfnWndProc = reinterpret_cast<WNDPROC>(DefWndProc);
	wex.hInstance = *phInstance;
	wex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wex.lpszClassName = windowName;
	RegisterClassEx(&wex);

	if (Screen::isFullScreen)
	{
		mHWND = CreateWindow(
			windowName, windowName,
			WS_VISIBLE | WS_POPUP,
			0, 0, 
			Screen::getDisplayWidth(),
			Screen::getDisplayHeight(),
			0, 0, *phInstance, 0);
		//•W€‚Ì•`‰æˆ—‚ð–³Œø‰»
		ValidateRect(mHWND, 0);
	}
	else
	{
		mHWND = CreateWindow(
			windowName, windowName,
			WS_OVERLAPPEDWINDOW,
			x, y, m_Width, m_Height,
			0, 0, *phInstance, 0);
	}

	pInstance = this;
}

WindowInstance::~WindowInstance()
{
	pInstance = nullptr;
}

void WindowInstance::show(int nCmdShow)
{
	ShowWindow(mHWND, SW_SHOW);
}

void WindowInstance::update()
{
	UpdateWindow(mHWND);
}

void WindowInstance::adjustWindowSize()
{
	RECT windowRect;
	RECT clientRect;

	GetWindowRect(mHWND, &windowRect);
	GetClientRect(mHWND, &clientRect);

	int adjustWidth = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + m_Width;
	int adjustHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + m_Height;

	SetWindowPos(mHWND, NULL, m_Position.x, m_Position.y, adjustWidth, adjustHeight, SWP_NOMOVE | SWP_NOZORDER);
}

HWND * WindowInstance::getHWND()
{
	return &pInstance->mHWND;
}

int WindowInstance::getWidth()
{
	return m_Width;
}

int WindowInstance::getHeight()
{
	return m_Height;
}
