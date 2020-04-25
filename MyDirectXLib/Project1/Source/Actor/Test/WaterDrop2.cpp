#include "WaterDrop2.h"
#include "Component\Physics\CircleCollider2D.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\ActionManager.h"
#include "Component\Transform.h"
#include "Utility\Action\Actions.h"

#include "Actor\Test\TestSplat.h"
#include "Actor\Test\SplashEffect.h"

#include "Utility\Random.h"
#include "Device\GameTime.h"

WaterDrop2::WaterDrop2(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void WaterDrop2::start()
{
	Random random;

	CircleCollider2D* pCollider = new CircleCollider2D(this, 16.0f);
	pCollider->layer = PhysicsLayer::Player;

	for (int i = 0; i < random.getRandom(3, 5); ++i)
	{
		auto pMetaBall = new GameObject(m_pGameMediator);
		pMetaBall->setParent(this);
		pMetaBall->setSize(Vec3(16.0f, 16.0f, 0.0f));

		float range = 8.0f;
		pMetaBall->getTransform()->setLocalPosition(Vec3(random.getRandom(-range, range), random.getRandom(-range, range), 0.0f));

		auto pActionM = new Action::ActionManager(pMetaBall);
		auto pSequence = new Action::Sequence(2, 
			new Action::EaseInOutBack(new Action::ScaleTo(Vec3(24.0f, 24.0f, 0.0f), random.getRandom(0.1f, 0.3f))),
			new Action::EaseInOutSine(new Action::ScaleTo(Vec3(16.0f, 16.0f, 0.0f), random.getRandom(0.1f, 0.3f)))
			);

		pActionM->enqueueAction(new Action::RepeatForever(pSequence));

		auto pSprite = new SpriteRenderer(pMetaBall);
		pSprite->setTextureByName("MetaBall");
		pSprite->setGraphicsLayer(GraphicsLayer::MetaBall);
	}
}

void WaterDrop2::update()
{
	setPosition(getPosition() - Vec3(0, m_Speed, 0) * GameTime::getDeltaTime());

	m_Speed += 9.8f * 100.0f * GameTime::getDeltaTime();
}

void WaterDrop2::onCollisionEnter(GameObject * pHit)
{
	auto pSplash = new SplashEffect(m_pGameMediator);
	pSplash->setPosition(getPosition());

	auto pSplat = new TestSplat(m_pGameMediator);
	pSplat->setPosition(getPosition());

	destroy();
}
