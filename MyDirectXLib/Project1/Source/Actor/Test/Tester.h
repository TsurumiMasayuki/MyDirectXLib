#pragma once
#include "Actor\GameObject.h"

class Tester
	: public GameObject
{
public:
	Tester(IGameMediator* pGameMediator);
	~Tester();

	virtual void start() override;
	virtual void update() override;

	virtual void onCollisionEnter(GameObject* pHit) override;
	virtual void onCollisionStay(GameObject* pHit) override;
	virtual void onCollisionExit(GameObject* pHit) override;
};