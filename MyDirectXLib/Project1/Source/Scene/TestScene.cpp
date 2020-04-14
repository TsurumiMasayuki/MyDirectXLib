#include "TestScene.h"
#include "Actor\GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\GameObject.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\Graphics\TextRenderer.h"
#include "Math\MathUtility.h"
#include "Device\Camera.h"
#include "Device\GameTime.h"
#include "Device\Input.h"
#include "Utility\Color.h"
#include <DirectXColors.h>

#include "Def\Screen.h"

#include "Actor\Test\Tester.h"
#include "Actor\Test\TestSplat.h"
#include "Component\Transform.h"
#include "Component\Physics\SphereCollider3D.h"
#include "Component\Physics\BoxCollider3D.h"
#include "Component\Graphics\PostEffect\MetaBallRenderer.h"
#include "Component\Graphics\PostEffect\SplashMask.h"
#include "Component\Graphics\PostEffect\DefaultRender.h"
#include "Component\ActionManager.h"
#include "Utility\Action\Actions.h"
#include "Utility\Random.h"

GameObject* controlObj = nullptr;

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	controlObj = new GameObject(this);
	controlObj->setSize(Vec3(32, 32, 0));
	controlObj->setPosition(Vec3(0, 0, 0));

	auto sprite = new SpriteRenderer(controlObj);
	sprite->setTextureByName("BoxFill");
	sprite->setGraphicsLayer(GraphicsLayer::Default);
	sprite->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	for (int i = 0; i < 4; i++)
	{
		auto newObj = new GameObject(this);
		newObj->setSize(Vec3(640, 96, 0));
		newObj->setPosition(Vec3(0, i * (720 / 4) - (720 * 0.5f), 0));

		auto sprite = new SpriteRenderer(newObj);
		sprite->setTextureByName("BoxFill");
		sprite->setGraphicsLayer(GraphicsLayer::Block);
		sprite->setColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
	}

	//Random random;

	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		auto newObj = new GameObject(this);
	//		float size = random.getRandom(32, 96);
	//		newObj->setSize(Vec3(size, size, 0));
	//		newObj->setPosition(Vec3(i * 32, j * 32, 0));

	//		auto sprite = new SpriteRenderer(newObj);
	//		sprite->setTextureByName("MetaBall");
	//		sprite->setGraphicsLayer(GraphicsLayer::Splash);
	//		sprite->setColor(Color(0.25f, 0.4f, 0.8f, 1.0f));

	//		auto action = new Action::ActionManager(newObj);
	//		action->enqueueAction(new Action::EaseInOutBounce(new Action::ScaleBy(Vec3(size * 3, size * 3, 0), 5.0f)));
	//	}
	//}

	auto postEffect = new GameObject(this);
	new DefaultRender(postEffect, 150, GraphicsLayer::Default);
	new DefaultRender(postEffect, 110, GraphicsLayer::Block);
	new SplashMask(postEffect, 150);
	//new MetaBallRenderer(postEffect);
	postEffect->setPosition(Vec3(0, 0, 0));
	postEffect->setSize(Vec3(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f));

	//auto postEffect = new GameObject(this);
	////new DefaultRender(postEffect, 150, GraphicsLayer::Default);
	//new DefaultRender(postEffect, 110, GraphicsLayer::Block);
	//new SplashMask(postEffect, 150);
	////new MetaBallRenderer(postEffect);
	//postEffect->setPosition(Vec3(-Screen::getWindowWidth() / 4, 0, 1.0f));
	//postEffect->setSize(Vec3(Screen::getWindowWidth() / 2, Screen::getWindowHeight() / 2, 1.0f));

	//auto postEffect2 = new GameObject(this);
	////new DefaultRender(postEffect2, 100, GraphicsLayer::Default);
	//new DefaultRender(postEffect2, 110, GraphicsLayer::Block);
	//new DefaultRender(postEffect2, 120, GraphicsLayer::Splash);
	////new SplashMask(postEffect2, 130);
	////new MetaBallRenderer(postEffect);
	//postEffect2->setPosition(Vec3(Screen::getWindowWidth() / 4, 0, 1.0f));
	//postEffect2->setSize(Vec3(Screen::getWindowWidth() / 2, Screen::getWindowHeight() / 2, 1.0f));
}

void TestScene::update()
{
	controlObj->setPosition(Input::getMousePosition());

	if (Input::isKeyDown(VK_LBUTTON))
	{
		auto splat = new TestSplat(this);
		splat->setPosition(Input::getMousePosition());
	}

	m_pObjManager->update();
	m_pPhysicsWorld->update();
}

void TestScene::shutdown()
{
	delete m_pObjManager;
	delete m_pPhysicsWorld;
}

std::string TestScene::nextScene()
{
	return "TestScene";
}

bool TestScene::isEnd()
{
	return false;
}

GameObjectManager * TestScene::getGameObjectManager()
{
	return m_pObjManager;
}

PhysicsWorld * TestScene::getPhysicsWorld()
{
	return m_pPhysicsWorld;
}
