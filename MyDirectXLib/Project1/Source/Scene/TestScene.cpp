#include "TestScene.h"
#include "Actor\GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\GameObject.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Component\Graphics\TextRenderer.h"
#include "Math\MathUtility.h"
#include "Device\GameTime.h"
#include "Device\Input.h"
#include "Utility\Color.h"
#include <DirectXColors.h>

#include "Actor\Test\Tester.h"
#include "Component\Transform.h"
#include "Component\Physics\SphereCollider3D.h"
#include "Component\Physics\BoxCollider3D.h"

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	//for (int i = 0; i < 100; ++i)
	//{
		auto tester = new Tester(this);
		tester->getTransform()->setSize(1.0f);
		//auto coll1 = new BoxCollider3D(tester);
		//coll1->setSize(Vec3(1.0f, 1.0f, 1.0f));
		//coll1->isTrigger = true;
	//}

	auto obj2 = new GameObject(this);
	auto text1 = new TextRenderer(obj2);
	text1->setFont(L"Meiryo", FONT_WEIGHT_BLACK, FONT_STYLE_NORMAL);
	text1->setTextSize(32.0f);
	text1->setText(L"Hello World!");
	text1->setColor(Color(DirectX::Colors::Red));
}

void TestScene::update()
{
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
