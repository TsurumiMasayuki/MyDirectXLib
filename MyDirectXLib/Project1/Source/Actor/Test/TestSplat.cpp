#include "TestSplat.h"
#include "Component\Graphics\CustomRenderer2D.h"

TestSplat::TestSplat(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

void TestSplat::start()
{
	auto renderer = new CustomRenderer2D(this);
	//���C���[�𐅂��Ԃ��p�ɃZ�b�g
	renderer->setGraphicsLayer(GraphicsLayer::Splash);
	renderer->setVertexShader("BasicVS");
	renderer->setPixelShader("CircleFillPS");

	
}

void TestSplat::update()
{
}
