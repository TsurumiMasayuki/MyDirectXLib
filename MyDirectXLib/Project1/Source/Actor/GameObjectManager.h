#pragma once
#include <vector>

class GameObject;
class RenderManager;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void update();
	void add(GameObject* pGameObject);
	void remove(GameObject* pGameObject);

private:
	void addObjects();
	void destroyObjects();

private:
	std::vector<GameObject*> m_GameObjects;
	std::vector<GameObject*> m_AddObjects;
};

