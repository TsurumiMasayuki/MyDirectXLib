#pragma once

class ICameraEffect
{
public:
	ICameraEffect() {};
	virtual ~ICameraEffect() {};

	virtual void update(float deltaTime) = 0;
	virtual bool isEnd() = 0;
};