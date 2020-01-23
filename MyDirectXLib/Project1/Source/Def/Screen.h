#pragma once

 class Screen
{
public:
	static const bool isFullScreen = false;

private:
	static const int m_Width = 1280;
	static const int m_Height = 720;

public:
	static int getDisplayWidth();
	static int getDisplayHeight();

	static int getWindowWidth();
	static int getWindowHeight();

private:
	Screen() {};
	Screen(const Screen&) = delete;
	~Screen() {};
};

