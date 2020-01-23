#pragma once
#include "Device\Camera.h"
#include "ICameraEffect.h"
#include <string>

class CameraEffectManager
{
public:
	static void startEffect(ICameraEffect* cameraEffect);
	static void effectUpdate(float deltaTime);
	static void shutdown();

private:
	CameraEffectManager();
	~CameraEffectManager();
};

