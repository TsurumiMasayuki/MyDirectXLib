#pragma once
#include "Actor\GameObject.h"

namespace Action
{
	class ActionManager;
}

class WaterDrop
	: public GameObject
{
public:
	WaterDrop(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void update() override;

	//virtual void onCollisionEnter(GameObject* pHit) override;
	//virtual void onCollisionStay(GameObject* pHit) override;
	//virtual void onCollisionExit(GameObject* pHit) override;

	Action::ActionManager* pActionM;
	float m_Speed;
};