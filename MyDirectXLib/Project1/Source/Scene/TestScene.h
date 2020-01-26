#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"

class TestScene
	: public AbstractScene, public IGameMediator
{
public:
	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void shutdown() override;
	virtual std::string nextScene() override;
	virtual bool isEnd() override;

	virtual GameObjectManager * getGameObjectManager() override;
	virtual PhysicsWorld * getPhysicsWorld() override;

private:
	GameObjectManager* m_pObjManager;
	PhysicsWorld* m_pPhysicsWorld;
};