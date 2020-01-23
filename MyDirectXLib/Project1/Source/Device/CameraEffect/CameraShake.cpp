#include "CameraShake.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Device\Camera.h"

CameraShake::CameraShake(float strength, float time, Vec3 shakeDirection)
	:mShakeStrength(strength), m_pTimer(new Timer(time)), mShakeDirection(shakeDirection)
{
}

CameraShake::~CameraShake()
{
	delete m_pTimer;
}

void CameraShake::update(float deltaTime)
{
	m_pTimer->update();

	float timeMutiply = 1 - m_pTimer->getRatioClamped();
	float sin = sinf(m_pTimer->getRatioClamped() * M_PI * 2) * timeMutiply * mShakeStrength;
	
	Camera::setPosition(mShakeDirection * sin);
}

bool CameraShake::isEnd()
{
	return m_pTimer->isTime();
}
