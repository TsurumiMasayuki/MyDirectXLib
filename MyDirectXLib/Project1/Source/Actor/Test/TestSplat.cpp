#include "TestSplat.h"
#include "Actor\Test\TestSplatNode.h"

#include "Utility\Random.h"

TestSplat::TestSplat(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void TestSplat::start()
{
	Random random;
	int nodeCount = random.getRandom(2, 5);

	for (int i = 0; i < nodeCount; i++)
	{
		//•ûŒü‚É‚Í‚È‚ç‚È‚¢‚¯‚ÇAˆÊ’u‚Ìƒ‰ƒ“ƒ_ƒ€«‚Ì‚½‚ß‚É‚ ‚¦‚Ä‘å‚«–Ú‚Ì”ÍˆÍ
		float range = 1.25f;
		float dirX = random.getRandom(-range, range);
		float dirY = random.getRandom(-range, range);
		auto pNewSplat = new TestSplatNode(m_pGameMediator, random.getRandom(48, 56), Vec2(dirX, dirY));
		pNewSplat->setPosition(getPosition());
	}
}

void TestSplat::update()
{
}
