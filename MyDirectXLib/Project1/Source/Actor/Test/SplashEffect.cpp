#include "SplashEffect.h"

#include "Utility\Random.h"
#include "Utility\Action\Actions.h"
#include "Component\ActionManager.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Utility\Timer.h"

SplashEffect::SplashEffect(IGameMediator * pGameMediator)
	: GameObject(pGameMediator),
	m_pTimer(new Timer(2.0f))
{
}

SplashEffect::~SplashEffect()
{
	delete m_pTimer;
}

void SplashEffect::start()
{
	Random random;

	//パーティクルの生成
	for (int i = 0; i < 4; ++i)
	{
		float randomX = random.getRandom(-0.5f, 0.5f);
		Vec3 direction(randomX, 1.0f - std::fabsf(randomX), 0.0f);

		auto pParicle = new GameObject(m_pGameMediator);
		pParicle->setPosition(getPosition());
		pParicle->setSize(Vec3(12.0f, 24.0f, 1.0f));
		pParicle->setParent(this);

		auto pSprite = new SpriteRenderer(pParicle);
		pSprite->setTextureByName("CircleFill");
		pSprite->setColor(Color(DirectX::Colors::Cyan));

		auto pAction = new Action::ActionManager(pParicle);
		auto pSpawn = new Action::Spawn(2,
			new Action::EaseInSine(new Action::MoveBy(direction * 32, 0.6f)),
			new Action::EaseInSine(new Action::ScaleTo(Vec3::zero(), 0.6f)));
		pAction->enqueueAction(pSpawn);
	}
}

void SplashEffect::update()
{
	m_pTimer->update();
	if (m_pTimer->isTime())
	{
		destroy();
	}
}