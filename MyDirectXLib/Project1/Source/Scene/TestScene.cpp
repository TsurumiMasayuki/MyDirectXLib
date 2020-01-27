#include "TestScene.h"
#include "Actor\GameObjectManager.h"
#include "Physics\PhysicsWorld.h"
#include "Actor\GameObject.h"
#include "Component\Graphics\MeshRenderer.h"
#include "Component\Graphics\SpriteRenderer.h"
#include "Math\MathUtility.h"
#include "Device\GameTime.h"
#include "Device\Input.h"

GameObject* obj = nullptr;

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	obj = new GameObject(this);
	auto renderer = new MeshRenderer(obj);
	renderer->setMesh("TestMesh");

	auto getComp = obj->getComponent<MeshRenderer>();
	getComp->setMesh("Cube");

	auto obj2 = new GameObject(this);
	obj2->setSize(Vec3(64, 64, 0));
	auto sprite = new SpriteRenderer(obj2);
	sprite->setTextureName("BoxOutline");
}

void TestScene::update()
{
	obj->setPosition(obj->getPosition() + Input::getLStickValue().toVec3() * 8 * GameTime::getDeltaTime());

	Vec3 angles = Input::getRStickValue().toVec3();
	obj->setAngles(obj->getAngles() + Vec3(angles.y, angles.x, 0) * 8 * GameTime::getDeltaTime());

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
