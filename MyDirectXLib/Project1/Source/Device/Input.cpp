#include "Input.h"
#include <sstream>
#include "Def\Screen.h"
#include "Device\Camera.h"

#define KEY_MAX 256

static BYTE mCurKeys[KEY_MAX];
static BYTE mPreKeys[KEY_MAX];

#define PRESSED 0x80

bool Input::isKeyUp(UINT key)
{
	return !(mCurKeys[key] & PRESSED) && (mPreKeys[key] & PRESSED);
}

bool Input::isKey(UINT key)
{
	return (mCurKeys[key] & PRESSED) && (mPreKeys[key] & PRESSED);
}

bool Input::isKeyDown(UINT key)
{
	return (mCurKeys[key] & PRESSED) && !(mPreKeys[key] & PRESSED);
}

Vec3 Input::getMousePosition()
{
	HWND hwnd = FindWindow("Project1", "Project1");

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(hwnd, &cursorPos);

	return Vec3(
		cursorPos.x - Screen::getWindowWidth() * 0.5f,
		-cursorPos.y + Screen::getWindowHeight() * 0.5f,
		0);
}

Vec3 Input::getWorldMousePosition()
{
	return getMousePosition() - Camera::getPosition();
}

void Input::update()
{
	memcpy_s(mPreKeys, sizeof(mPreKeys), mCurKeys, sizeof(mCurKeys));
	GetKeyboardState(mCurKeys);
}
