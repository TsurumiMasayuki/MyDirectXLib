#include "Tester.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Utility\Color.h"
#include <DirectXColors.h>
#include "Device\Input.h"
#include "Device\GameTime.h"
#include "Component\Transform.h"
#include "Component\Audio\AudioSource.h"
#include "Math\Easing.h"
#include "Utility\Timer.h"
#include "Component\ActionManager.h"
#include "Utility\Action\Actions.h"

float deathTimer = 0.0f;
Timer timer;

using namespace Action;

Tester::Tester(IGameMediator * pGameMediator)
	: GameObject(pGameMediator)
{
}

Tester::~Tester()
{
}

void Tester::start()
{
	auto renderer = new MeshRenderer(this);
	renderer->setMesh("Vox");
	renderer->setColor(Color(DirectX::Colors::White));
	timer = Timer(3.0f);

	auto audio = new AudioSource(this);
	audio->setAudio("MusicMono");
	audio->play();

	auto actionManager = new Action::ActionManager(this);
	actionManager->enqueueAction(new Repeat(new EaseInBack(new MoveBy(Vec3(1, 0, 0), 1.0f)), 3));
}

void Tester::update()
{
	//表示テスト用
	//getTransform()->setPosition(getTransform()->getPosition() + Input::getLStickValue().toVec3() * 3 * GameTime::getDeltaTime());
	//getTransform()->setPosition(getTransform()->getPosition() + Vec3(0, 0, -1 * Input::isPadButton(Input::PAD_BUTTON_A)) * 3 * GameTime::getDeltaTime());
	//getTransform()->setAngles(getTransform()->getAngles() + Input::getRStickValue().toVec3() * 30 * GameTime::getDeltaTime());
}

void Tester::onCollisionEnter(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Red));
}

void Tester::onCollisionStay(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Yellow));

	//deathTimer += GameTime::getDeltaTime();
	//if (deathTimer >= 3)
	//{
	//	destroy();
	//	pHit->destroy();
	//}
}

void Tester::onCollisionExit(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Green));
}
