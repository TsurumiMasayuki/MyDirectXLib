#ifndef _TESTSPLATNODE_H_
#define _TESTSPLATNODE_H_

#include "Actor\GameObject.h"
#include "Math\Vec2.h"

class Timer;

class TestSplatNode
	: public GameObject
{
public:
	TestSplatNode(IGameMediator* pGameMediator, float destSize, const Vec2& direction);
	~TestSplatNode();

	virtual void start() override;
	virtual void update() override;

private:
	bool m_CreateChild;
	float m_DestSize;
	Vec2 m_Direction;
	Timer* m_pTimer;

	static const float minSize;
};

#endif // !_TESTSPLATNODE_H_
