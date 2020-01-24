#include "Input.h"
#include <sstream>
#include "Def\Screen.h"
#include "Device\Camera.h"
#include "Math\MathUtility.h"

BYTE Input::m_CurKeys[256];
BYTE Input::m_PreKeys[256];

JOYINFOEX Input::m_CurPadInfo;
JOYINFOEX Input::m_PrePadInfo;

bool Input::m_isPadConnected = false;

#define PRESSED 0x80
#define JOYSTICK_CENTER 32767.0f
#define JOYSTICK_MAX 65535.0f

bool Input::isKeyUp(UINT key)
{
	return !(m_CurKeys[key] & PRESSED) && (m_PreKeys[key] & PRESSED);
}

bool Input::isKey(UINT key)
{
	return (m_CurKeys[key] & PRESSED) && (m_PreKeys[key] & PRESSED);
}

bool Input::isKeyDown(UINT key)
{
	return (m_CurKeys[key] & PRESSED) && !(m_PreKeys[key] & PRESSED);
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

bool Input::isPadButtonUp(PAD_BUTTON button)
{
	return m_isPadConnected && !(m_CurPadInfo.dwButtons & button) && (m_PrePadInfo.dwButtons & button);
}

bool Input::isPadButton(PAD_BUTTON button)
{
	return m_isPadConnected && (m_CurPadInfo.dwButtons & button) && (m_PrePadInfo.dwButtons & button);
}

bool Input::isPadButtonDown(PAD_BUTTON button)
{
	return  m_isPadConnected && (m_CurPadInfo.dwButtons & button) && !(m_PrePadInfo.dwButtons & button);
}

Vec2 Input::getDPadValue()
{
	if (!m_isPadConnected)
		return Vec2::zero();

	Vec2 axis;
	//左入力されていたら
	if (m_CurPadInfo.dwPOV == JOY_POVLEFT)
	{
		axis.x = -1;
		axis.y = 0;
	}

	//右入力されていたら
	if (m_CurPadInfo.dwPOV == JOY_POVRIGHT)
	{
		axis.x = 1;
		axis.y = 0;
	}

	//上入力されていたら
	if (m_CurPadInfo.dwPOV == JOY_POVFORWARD)
	{
		axis.x = 0;
		axis.y = 1;
	}

	//上入力されていたら
	if (m_CurPadInfo.dwPOV == JOY_POVBACKWARD)
	{
		axis.x = 0;
		axis.y = -1;
	}

	return axis;
}

Vec2 Input::getLStickValue()
{
	if (!m_isPadConnected)
		return Vec2::zero();

	Vec2 axis(0, 0);
	//-JOYSTICK_CENTER ~ +JOYSTICK_CENTERの間に値を修正
	float centeredX = (m_CurPadInfo.dwXpos - JOYSTICK_CENTER);
	float centeredY = (m_CurPadInfo.dwYpos - JOYSTICK_CENTER);

	//-1 ~ 1の間に変換
	if (centeredX != 0)
		axis.x = MathUtility::clamp(centeredX / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1の間に変換(Yの場合は符号を逆にする)
	if (centeredY != 0)
		axis.y = MathUtility::clamp(centeredY / JOYSTICK_CENTER, -1.0f, 1.0f) * -1.0f;

	return axis;
}

Vec2 Input::getRStickValue()
{
	if (!m_isPadConnected)
		return Vec2::zero();

	Vec2 axis(0, 0);
	//-JOYSTICK_CENTER ~ +JOYSTICK_CENTERの間に値を修正
	float centeredZ = (m_CurPadInfo.dwZpos - JOYSTICK_CENTER);
	float centeredR = (m_CurPadInfo.dwRpos - JOYSTICK_CENTER);

	//-1 ~ 1の間に変換
	if (centeredZ != 0)
		axis.x = MathUtility::clamp(centeredZ / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1の間に変換(Yの場合は符号を逆にする)
	if (centeredR != 0)
		axis.y = MathUtility::clamp(centeredR / JOYSTICK_CENTER, -1.0f, 1.0f) * -1.0f;

	return axis;
}

void Input::update()
{
	//前フレームのキーボード入力をコピー
	memcpy_s(m_PreKeys, sizeof(m_PreKeys), m_CurKeys, sizeof(m_CurKeys));
	//現在のフレームのキーボード入力を取得
	GetKeyboardState(m_CurKeys);

	//前フレームの状態をコピー
	m_PrePadInfo = m_CurPadInfo;

	//取得したいデータのサイズ指定(RETURNALLを指定しているので構造体と同じ)
	m_CurPadInfo.dwSize = sizeof(JOYINFOEX);
	m_CurPadInfo.dwFlags = JOY_RETURNALL;

	bool noError = false;

	m_isPadConnected = false;

	//接続されているコントローラーを探す
	for (int i = 0; i < joyGetNumDevs(); i++)
	{
		//問題なく接続されているコントローラーが見つかったら終了
		if (joyGetPosEx(i, &m_CurPadInfo) == JOYERR_NOERROR)
		{
			noError = true;
			m_isPadConnected = true;
			break;
		}
	}
}
