#include "TestSplat.h"
#include "Component\Graphics\CustomRenderer2D.h"

TestSplat::TestSplat(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void TestSplat::start()
{
	auto renderer = new CustomRenderer2D(this);
	//レイヤーを水しぶき用にセット
	renderer->setGraphicsLayer(GraphicsLayer::Splash);
	renderer->setVertexShader("BasicVS");
	renderer->setPixelShader("CircleFillPS");

	
}

void TestSplat::update()
{
}
