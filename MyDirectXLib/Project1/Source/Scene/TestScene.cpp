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
#include "Actor\Test\WaterDrop.h"
#include "Actor\Test\WaterDrop2.h"

#include "Component\Transform.h"
#include "Component\Physics\SphereCollider3D.h"
#include "Component\Physics\BoxCollider2D.h"
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

	//for (int i = 0; i < 4; i++)
	//{
	//	auto newObj = new GameObject(this);
	//	newObj->setSize(Vec3(640, 96, 0));
	//	newObj->setPosition(Vec3(0, i * (720 / 4) - (720 * 0.5f), 0));

	//	auto sprite = new SpriteRenderer(newObj);
	//	sprite->setTextureByName("BoxFill");
	//	sprite->setGraphicsLayer(GraphicsLayer::Block);
	//	sprite->setColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
	//}

	auto block = new GameObject(this);
	block->setSize(Vec3(640, 96, 0));
	block->setPosition(Vec3(0, -360, 0));

	auto blockRenderer = new SpriteRenderer(block);
	blockRenderer->setTextureByName("BoxFill");
	blockRenderer->setGraphicsLayer(GraphicsLayer::Block);
	blockRenderer->setColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

	auto pCollider = new BoxCollider2D(block);
	pCollider->setWidth(640.0f);
	pCollider->setHeight(96.0f);

	auto postEffect = new GameObject(this);
	new DefaultRender(postEffect, 150, GraphicsLayer::Default);
	new DefaultRender(postEffect, 110, GraphicsLayer::Block);

	new SplashMask(postEffect, 150);
	new MetaBallRenderer(postEffect);

	postEffect->setPosition(Vec3(0, 0, 0));
	postEffect->setSize(Vec3(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f));

	//auto postEffect2 = new GameObject(this);
	////new DefaultRender(postEffect2, 100, GraphicsLayer::Default);
	//new DefaultRender(postEffect2, 110, GraphicsLayer::Block);
	//new DefaultRender(postEffect2, 120, GraphicsLayer::Splash);
	////new SplashMask(postEffect2, 130);
	////new MetaBallRenderer(postEffect);
	//postEffect2->setPosition(Vec3(Screen::getWindowWidth() / 4, 0, 1.0f));
	//postEffect2->setSize(Vec3(Screen::getWindowWidth() / 2, Screen::getWindowHeight() / 2, 1.0f));

	m_Timer.setMaxTime(0.01f);
	m_DropCount = 64;
}

void TestScene::update()
{
	controlObj->setPosition(Input::getMousePosition());

	m_Timer.update();

	//if (Input::isKeyDown(VK_LBUTTON))
	//{
	//	auto splat = new TestSplat(this);
	//	splat->setPosition(Input::getMousePosition());
	//}

	if (Input::isKeyDown(VK_LBUTTON))
	{
		m_DropCount = 0;

		//auto pWaterDrop = new WaterDrop2(this);
		//pWaterDrop->setPosition(Input::getMousePosition());
	}

	if (m_Timer.isTime() && m_DropCount < 40)
	{
		m_Timer.reset();

		Random random;

		//for (int i = 0; i < random.getRandom(1, 3); i++)
		//{
		//	auto pWaterDrop = new WaterDrop(this);
		//	pWaterDrop->setPosition(Vec3(m_DropCount * 16 + random.getRandom(-8.0f, 8.0f), 360 + random.getRandom(-16.0f, 16.0f), 0));

		//	auto pWaterDrop2 = new WaterDrop(this);
		//	pWaterDrop2->setPosition(Vec3(m_DropCount * -16 + random.getRandom(-8.0f, 8.0f) + random.getRandom(-16.0f, 16.0f), 360, 0));
		//}

		float increment = 640 / 40;

		auto pWaterDrop = new WaterDrop2(this);
		pWaterDrop->setPosition(Vec3(m_DropCount * increment + random.getRandom(-8.0f, 8.0f), 360 + random.getRandom(-16.0f, 16.0f), 0));

		auto pWaterDrop2 = new WaterDrop2(this);
		pWaterDrop2->setPosition(Vec3(m_DropCount * -increment + random.getRandom(-8.0f, 8.0f), 360 + random.getRandom(-16.0f, 16.0f), 0));

		m_DropCount++;
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
