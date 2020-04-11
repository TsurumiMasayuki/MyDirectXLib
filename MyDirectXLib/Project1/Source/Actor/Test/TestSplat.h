#pragma once
#include "Actor\GameObject.h"

class TestSplat
	: public GameObject
{
public:
	TestSplat(IGameMediator* pGameMediator);

	virtual void start() override;
	virtual void update() override;
};