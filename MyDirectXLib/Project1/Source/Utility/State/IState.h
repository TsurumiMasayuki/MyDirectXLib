#pragma once

class IState
{
public:
	virtual ~IState() {};

	virtual void update() = 0;

	virtual void onStateEnter() = 0;
	virtual void onStateExit() = 0;

	virtual IState* nextState() = 0;
};