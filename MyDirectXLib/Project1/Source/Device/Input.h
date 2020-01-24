#pragma once
#include <Windows.h>
#include <joystickapi.h>
#include "Math\Vec3.h"
#include "Math\Vec2.h"

//ジョイスティック使用に必要なライブラリをリンク
#pragma comment(lib, "Winmm.Lib")

class Input
{
public:
	//コントローラーのボタン指定用Enum
	enum PAD_BUTTON
	{
		PAD_BUTTON_X = 0x0001,			//Xボタン
		PAD_BUTTON_Y = 0x0002,			//Yボタン
		PAD_BUTTON_A = 0x0004,			//Aボタン
		PAD_BUTTON_B = 0x0008,			//Bボタン
		PAD_BUTTON_LB = 0x00000010l,	//Lボタン
		PAD_BUTTON_RB = 0x00000020l,	//Rボタン
		PAD_BUTTON_LT = 0x00000040l,	//Lトリガー
		PAD_BUTTON_RT = 0x00000080l,	//Rトリガー
		PAD_BUTTON_START = 0x00000800l,	//スタートボタン
	};

	//指定されたキーが離された時にTrueを返します
	static bool isKeyUp(UINT key);
	//指定されたキーが押され続けている時にTrueを返します
	static bool isKey(UINT key);
	//指定されたキーが押された時にTrueを返します
	static bool isKeyDown(UINT key);

	//マウスの座標を返します
	static Vec3 getMousePosition();
	//カメラ基準でマウス座標を返します
	static Vec3 getWorldMousePosition();

	//コントローラーのボタンが離された時にTrueを返します
	static bool isPadButtonUp(PAD_BUTTON button);
	//コントローラーのボタン押され続けている時にTrueを返します
	static bool isPadButton(PAD_BUTTON button);
	//コントローラーのボタンが押された時にTrueを返します
	static bool isPadButtonDown(PAD_BUTTON button);

	//十字ボタン(名前がわからない)の入力を(-1 ~ 1, -1 ~ 1)の範囲で取得します
	static Vec2 getDPadValue();
	//左スティックの入力を(-1 ~ 1, -1 ~ 1)の範囲で取得します
	static Vec2 getLStickValue();
	//右スティックの入力を(-1 ~ 1, -1 ~ 1)の範囲で取得します
	static Vec2 getRStickValue();

	static void update();

private:
	static BYTE m_CurKeys[256];
	static BYTE m_PreKeys[256];

	static JOYINFOEX m_CurPadInfo;
	static JOYINFOEX m_PrePadInfo;

	static bool m_isPadConnected;
};

