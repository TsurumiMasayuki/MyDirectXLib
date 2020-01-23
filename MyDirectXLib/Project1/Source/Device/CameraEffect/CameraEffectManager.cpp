#include "CameraEffectManager.h"
#include <vector>

std::vector<ICameraEffect*> cameraEffects;

void CameraEffectManager::startEffect(ICameraEffect* cameraEffect)
{
	cameraEffects.emplace_back(cameraEffect);
}

void CameraEffectManager::effectUpdate(float deltaTime)
{
	for (auto effect : cameraEffects)
	{
		effect->update(deltaTime);
	}

	auto itr = cameraEffects.begin();
	while (itr != cameraEffects.end())
	{
		if ((*itr)->isEnd())
		{
			delete *itr;
			itr = cameraEffects.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	cameraEffects.shrink_to_fit();
}

void CameraEffectManager::shutdown()
{
	for (auto effect : cameraEffects)
	{
		delete effect;
	}
	cameraEffects.clear();
	cameraEffects.shrink_to_fit();
}

CameraEffectManager::CameraEffectManager()
{
}

CameraEffectManager::~CameraEffectManager()
{
}
