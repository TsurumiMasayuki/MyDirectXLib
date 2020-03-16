#include "Tester.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\SpriteRenderer.h"
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
#include "Utility\Random.h"
#include "Component\Test\SimpleMove.h"

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
	new SimpleMove(this);

	auto renderer = new MeshRenderer(this);
	renderer->setMesh("Sphere");
	renderer->setColor(Color(DirectX::Colors::White));
	setSize(Vec3(1, 1, 1));

	//setSize(Vec3(256, 256, 0));
	//auto renderer = new SpriteRenderer(this);
	//renderer->setTextureName("CircleFill");
	//renderer->setColor(Color(0.8f, 0.5f, 0.5f, 1.0f));

	auto audio = new AudioSource(this);
	audio->setAudio("MusicMono");
	//audio->play();

	Random random;

	//auto actionManager = new Action::ActionManager(this);
	//auto sequence = new Sequence(
	//	3,
	//	new EaseInSine(new MoveTo(Vec3(random.getRandom(-640.0f, -320.0f), 0, 0), 1)),
	//	new EaseInSine(new MoveTo(Vec3(0, random.getRandom(-360.0f, 360.0f), 0), 1)),
	//	new EaseInSine(new MoveTo(Vec3(random.getRandom(320.0f, 640.0f), 0, 0), 1))
	//);

	//actionManager->enqueueAction(new RepeatForever(sequence));
}

void Tester::update()
{
	//表示テスト用
	//getTransform()->setPosition(getTransform()->getPosition() + Input::getLStickValue().toVec3() * 3 * GameTime::getDeltaTime());
	//getTransform()->setPosition(getTransform()->getPosition() + Vec3(0, 0, -1 * Input::isPadButton(Input::PAD_BUTTON_A)) * 3 * GameTime::getDeltaTime());

	//Vec3 rStick = Input::getRStickValue().toVec3();
	//Vec3 rotate = Vec3(rStick.y, -rStick.x, 0) * 120 * GameTime::getDeltaTime();
	//getTransform()->setAngles(getTransform()->getAngles() + rotate);
}

void Tester::onCollisionEnter(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Red));
}

void Tester::onCollisionStay(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Yellow));
}

void Tester::onCollisionExit(GameObject * pHit)
{
	getComponent<MeshRenderer>()->setColor(Color(DirectX::Colors::Green));
}
