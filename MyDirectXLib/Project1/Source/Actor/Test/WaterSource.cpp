#include "WaterSource.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\Transform.h"
#include "Component\ActionManager.h"
#include "Utility\Action\Actions.h"
#include "Utility\Random.h"
#include "Device\Input.h"

WaterSource::WaterSource(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void WaterSource::start()
{
	Random random;
	int metaBallCount = random.getRandom(3, 5);

	setSize(Vec3(32.0f, 32.0f, 32.0f));

	auto pSprite = new SpriteRenderer(this);
	pSprite->setTextureByName("BoxFill");
	pSprite->setGraphicsLayer(GraphicsLayer::Block);
	pSprite->setColor(Color(DirectX::Colors::LightGray));

	for (int i = 0; i < metaBallCount; i++)
	{
		auto pMetaBall = new GameObject(m_pGameMediator);
		addChild(*pMetaBall);

		Vec3 pos(getSize().x / metaBallCount * i - getSize().x / 2, -getSize().y * 0.5f, 0);
		pMetaBall->getTransform()->setLocalPosition(pos);
		pMetaBall->setSize(Vec3(30.0f, 30.0f, 1.0f));

		auto pActionM = new Action::ActionManager(pMetaBall);
		auto pSequence = new Action::Sequence(2,
			new Action::EaseInOutCirc(new Action::ScaleTo(Vec3(48.0f, 48.0f, 1.0f), random.getRandom(0.5f, 3.0f))),
			new Action::EaseInOutCirc(new Action::ScaleTo(Vec3(30.0f, 30.0f, 1.0f), random.getRandom(0.5f, 3.0f)))
		);

		pActionM->enqueueAction(new Action::RepeatForever(pSequence));

		auto pSprite = new SpriteRenderer(pMetaBall);
		pSprite->setTextureByName("MetaBall");
		pSprite->setGraphicsLayer(GraphicsLayer::MetaBall);
	}
}

void WaterSource::update()
{
	if (Input::isKeyDown(VK_LBUTTON))
	{
		//auto children = getChildren();
		//for (auto pChild : children)
		//{
		//	pChild->setActive(false);
		//}
	}
}
