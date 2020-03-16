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
#include "Utility\Random.h"

void TestScene::init()
{
	m_pObjManager = new GameObjectManager();
	m_pPhysicsWorld = new PhysicsWorld(this);

	//auto obj1 = new Tester(this);

	//auto obj2 = new GameObject(this);
	//auto text1 = new TextRenderer(obj2, 110);
	//text1->setFont(L"Meiryo", FONT_WEIGHT_BLACK, FONT_STYLE_NORMAL);
	//text1->setTextSize(32.0f);
	//text1->setText(L"Hello World!");
	//text1->setColor(Color(DirectX::Colors::Red));

	Random random;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			auto newObj = new GameObject(this);
			float size = random.getRandom(32, 96);
			newObj->setSize(Vec3(size, size, 0));
			newObj->setPosition(Vec3(i * 48, j * 48, 0));

			auto sprite = new SpriteRenderer(newObj);
			sprite->setTextureName("MetaBall");
		}
	}
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
