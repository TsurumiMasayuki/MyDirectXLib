#include "TestSplat.h"
#include "Component\Graphics\CustomRenderer2D.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\ActionManager.h"

#include "Utility\Random.h"
#include "Utility\Action\Actions.h"
#include "Utility\Action\EasingActions.h"

TestSplat::TestSplat(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void TestSplat::start()
{
	setSize(Vec3(0.0f, 0.0f, 1));

	auto renderer = new SpriteRenderer(this);
	//レイヤーを水しぶき用にセット
	renderer->setGraphicsLayer(GraphicsLayer::Splash);
	renderer->setTextureByName("CircleFill");
	renderer->setColor(Color(0.25f, 0.3f, 0.8f, 1.0f));


	Random random;
	float destScale = random.getRandom(32, 96);

	auto actionManager = new Action::ActionManager(this);
	actionManager->enqueueAction(new Action::ScaleTo(Vec3(destScale, destScale, 1.0f), 0.3f));
}

void TestSplat::update()
{
}
