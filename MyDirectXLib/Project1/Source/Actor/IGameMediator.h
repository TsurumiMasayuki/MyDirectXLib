#pragma once

class GameObjectManager;
class PhysicsWorld;

class IGameMediator
{
public:
	virtual ~IGameMediator() {};

	virtual GameObjectManager* getGameObjectManager() = 0;
	virtual PhysicsWorld* getPhysicsWorld() = 0;

private:
	IGameMediator() {};
	
};