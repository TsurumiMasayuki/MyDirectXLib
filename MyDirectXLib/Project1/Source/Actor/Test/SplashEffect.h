#pragma once
#include "Actor\GameObject.h"

class Timer;

class SplashEffect
	: public GameObject
{
public:
	SplashEffect(IGameMediator* pGameMediator);
	~SplashEffect();

	virtual void start() override;
	virtual void update() override;

private:
	Timer* m_pTimer;
};