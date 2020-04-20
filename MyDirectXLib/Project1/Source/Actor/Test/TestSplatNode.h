#ifndef _TESTSPLATNODE_H_
#define _TESTSPLATNODE_H_

#include "Actor\GameObject.h"
#include "Math\Vec2.h"

class Timer;

class TestSplatNode
	: public GameObject
{
public:
	TestSplatNode(IGameMediator* pGameMediator, float destSize, float shrinkRate, float minSize, const Vec2& direction);
	~TestSplatNode();

	virtual void start() override;
	virtual void update() override;

private:
	bool m_CreateChild;
	float m_DestSize;
	float m_MinSize;
	float m_ShrinkRate;
	Vec2 m_Direction;
	Timer* m_pTimer;
};

#endif // !_TESTSPLATNODE_H_
