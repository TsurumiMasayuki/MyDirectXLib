#pragma once
#include "Actor\GameObject.h"

class WaterSource
	: public GameObject
{
public:
	WaterSource(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void update() override;

	//virtual void onCollisionEnter(GameObject* pHit) override;
	//virtual void onCollisionStay(GameObject* pHit) override;
	//virtual void onCollisionExit(GameObject* pHit) override;
};