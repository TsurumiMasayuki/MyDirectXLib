#pragma once
#include <Windows.h>
#include "Math/Vec3.h"

class Input
{
public:
	static bool isKeyUp(UINT key);
	static bool isKey(UINT key);
	static bool isKeyDown(UINT key);

	static Vec3 getMousePosition();
	static Vec3 getWorldMousePosition();

	static void update();
};

