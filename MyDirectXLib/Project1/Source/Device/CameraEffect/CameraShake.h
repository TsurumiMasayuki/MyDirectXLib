#pragma once
#include "ICameraEffect.h"
#include "Math\Vec3.h"
#include "Utility\Timer.h"

class CameraShake
	:public ICameraEffect
{
public:
	CameraShake(float strength, float time, Vec3 shakeDirection);
	~CameraShake();

	virtual void update(float deltaTime) override;
	virtual bool isEnd() override;

private:
	float mShakeStrength;
	Timer* m_pTimer;
	Vec3 mShakeDirection;
};

