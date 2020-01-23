#include "Screen.h"
#include <Windows.h>

int Screen::getDisplayWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::getDisplayHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

int Screen::getWindowWidth()
{
	if (isFullScreen) 
		return getDisplayWidth();
	return m_Width;
}

int Screen::getWindowHeight()
{
	if (isFullScreen) 
		return getDisplayHeight();
	return m_Height;
}