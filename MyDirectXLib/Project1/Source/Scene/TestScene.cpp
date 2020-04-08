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
#include "Component\ActionManager.h"
#include "Utility\Action\Actions.h"
#include "Utility\Random.h"

GameObject* controlObj = nullptr;

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

	controlObj = new GameObject(this);
	controlObj->setSize(Vec3(48, 48, 0));
	controlObj->setPosition(Vec3(0, 0, 0));

	auto sprite = new SpriteRenderer(controlObj);
	sprite->setTextureName("MetaBall");

	Random random;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			auto newObj = new GameObject(this);
			float size = random.getRandom(32, 96);
			newObj->setSize(Vec3(size, size, 0));
			newObj->setPosition(Vec3(i * 32, j * 32, 0));

			auto sprite = new SpriteRenderer(newObj);
			sprite->setTextureName("MetaBall");

			auto action = new Action::ActionManager(newObj);
			action->enqueueAction(new Action::EaseInOutBounce(new Action::ScaleBy(Vec3(size * 3, size * 3, 0), 5.0f)));
		}
	}
}

void TestScene::update()
{
	controlObj->setPosition(Input::getMousePosition());

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
