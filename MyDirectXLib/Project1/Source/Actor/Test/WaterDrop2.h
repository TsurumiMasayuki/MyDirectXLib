#pragma once
#include "Actor\GameObject.h"

namespace Action
{
	class ActionManager;
}

class WaterDrop2
	: public GameObject
{
public:
	WaterDrop2(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void update() override;

	virtual void onCollisionEnter(GameObject* pHit) override;
	//virtual void onCollisionStay(GameObject* pHit) override;
	//virtual void onCollisionExit(GameObject* pHit) override;

	float m_Speed;
};