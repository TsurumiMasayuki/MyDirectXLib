#pragma once
#include <windows.h>

class WindowInstance
{
public:
	WindowInstance(
		HINSTANCE * hInstance,
		LPCSTR windowName,
		int x, int y);
	~WindowInstance();

	void show(int nCmdShow);
	void update();
	void adjustWindowSize();

	static HWND* getHWND();
	int getWidth();
	int getHeight();

public:
	POINT m_Position;

private:
	HWND mHWND;
	UINT m_Width;
	UINT m_Height;

	static WindowInstance* pInstance;
};

