#include "TestScene.h"
#include "Actor\GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\GameObject.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Math\MathUtility.h"
#include "Device\GameTime.h"

GameObject* obj = nullptr;
float angleZ;

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	obj = new GameObject(this);
	auto renderer = new MeshRenderer(obj);
	renderer->setMesh("TestMesh");
}

void TestScene::update()
{
	obj->setPosition(Vec3(angleZ, 0, 0));
	obj->setAngleZ(MathUtility::toRadian(angleZ += 1 * GameTime::getDeltaTime()));

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
