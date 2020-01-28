#include "TestScene.h"
#include "Actor\GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\GameObject.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Math\MathUtility.h"
#include "Device\GameTime.h"
#include "Device\Input.h"
#include "Utility\Color.h"
#include <DirectXColors.h>

#include "Actor\Test\Tester.h"
#include "Component\Physics\SphereCollider3D.h"

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	auto tester = new Tester(this);
	auto coll1 = new SphereCollider3D(tester);
	coll1->setRadius(1.0f);
	coll1->isTrigger = false;

	auto obj2 = new GameObject(this);
	obj2->setPosition(Vec3(2, 1, 0));

	auto renderer = new MeshRenderer(obj2);
	renderer->setMesh("Sphere");
	renderer->setColor(Color(DirectX::Colors::White));
	
	auto coll2 = new SphereCollider3D(obj2);
	coll2->setRadius(1.0f);
	coll2->isTrigger = false;
	coll2->isMove = false;
}

void TestScene::update()
{
	m_pObjManager->update();
	m_pPhysicsWorld->update();
}

void TestScene::draw()
{
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
