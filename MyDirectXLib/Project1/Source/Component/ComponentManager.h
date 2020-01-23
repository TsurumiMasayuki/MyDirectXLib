#pragma once
#include <vector>

class GameObject;
class AbstractComponent;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	void add(AbstractComponent* pComponent);
	void remove(AbstractComponent* pComponent);

	void update();

	void onEnable();
	void onDisable();
	void onDestroy();

	void onCollisionEnter(GameObject* pHit);
	void onCollisionStay(GameObject* pHit);
	void onCollisionExit(GameObject* pHit);

	//GetComponentŽÀ‘•‚·‚é

private:
	std::vector<AbstractComponent*> m_Components;
};

