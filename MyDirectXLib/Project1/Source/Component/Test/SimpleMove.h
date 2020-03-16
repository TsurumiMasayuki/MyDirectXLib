#pragma once
#include "Component\AbstractComponent.h"

class SimpleMove
	: public AbstractComponent
{
public:
	SimpleMove(GameObject* pUser) : AbstractComponent(pUser), speed(3)
	{
	}
	virtual void onStart() override;
	virtual void onUpdate() override;

	float speed;
};