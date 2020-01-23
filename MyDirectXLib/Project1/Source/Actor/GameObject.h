#pragma once
#include <vector>
#include <string>
#include "Math/Vec3.h"

class AbstractComponent;
class AbstractCollider2D;
class ComponentManager;
class IGameMediator;

class GameObject
{
public:
	GameObject(IGameMediator* pGameMediator);
	virtual ~GameObject();

	void objUpdate();
	void addComponent(AbstractComponent* pComponent);
	void removeComponent(AbstractComponent* pComponent);

	void addCollider(AbstractCollider2D* pCollider);
	AbstractCollider2D* getCollider();
	void removeCollider();

	bool compareTag(std::string tag);

	void destroy();
	bool isDestroy();

	void checkCollision();

	void onCollisionEnterCallBack(GameObject* pHit);
	void onCollisionStayCallBack(GameObject* pHit);
	void onCollisionExitCallBack(GameObject* pHit);

	IGameMediator* getGameMediator();

#pragma region getter/setter

	void setPosition(Vec3 position);
	Vec3 getPosition();

	void setAngleZ(float angle);
	float getAngleZ();

	void setAngles(Vec3 angles);
	Vec3 getAngles();

	void setSize(float size);
	void setSize(Vec3 size);
	Vec3 getSize();

	void setActive(bool value);
	bool isActive();

	void setTag(std::string tag);
	std::string getTag();

#pragma endregion

protected:
	virtual void start() {}
	virtual void update() {}
	virtual void onDestroy() {}

	virtual void onCollisionEnter(GameObject* pHit) {}
	virtual void onCollisionStay(GameObject* pHit) {};
	virtual void onCollisionExit(GameObject* pHit) {};

private:
	void objStart();
	void objOnDestroy();

protected:
	IGameMediator* m_pGameMediator;

private:
	Vec3 m_Position;
	Vec3 m_Angles;
	Vec3 m_Size;

	bool m_Enabled;
	bool m_DestroyFlag;
	bool m_FirstUpdate;

	std::string m_Tag;

	AbstractCollider2D* m_pCollider;
	ComponentManager* m_pComponentManager;
};

