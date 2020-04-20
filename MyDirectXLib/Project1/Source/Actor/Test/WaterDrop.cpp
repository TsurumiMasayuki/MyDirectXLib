#include "WaterDrop.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\ActionManager.h"
#include "Utility\Action\Actions.h"

#include "Utility\Random.h"
#include "Device\GameTime.h"
#include <DirectXColors.h>

WaterDrop::WaterDrop(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void WaterDrop::start()
{
	auto pRenderer = new SpriteRenderer(this);
	pRenderer->setTextureByName("BoxFill");
	pRenderer->setGraphicsLayer(GraphicsLayer::Default);
	pRenderer->setPivot(Vec2(0.5f, 1.0f));

	Color color(DirectX::Colors::DarkBlue);
	color.a = 0.5f;
	pRenderer->setColor(color);

	Random random;
	float width = random.getRandom(1.0f, 3.0f);
	setSize(Vec3(width, 0.0f, 0.0f));

	//pActionM = new Action::ActionManager(this);
	//pActionM->enqueueAction(new Action::EaseOutSine(new Action::ScaleTo(Vec3(width, random.getRandom(96, 512), 0.0f), 0.5f)));
}

void WaterDrop::update()
{
	setPosition(getPosition() - Vec3(0, m_Speed, 0) * GameTime::getDeltaTime());
	setSize(getSize() + Vec3(0.0f, m_Speed * 0.25f, 0.0f));

	m_Speed += 9.8f * 10.0f * GameTime::getDeltaTime();
}
