#pragma once
class GameObject;
class RenderManager;

class AbstractComponent
{
public:
	virtual ~AbstractComponent();

	void destroy();
	void setActive(bool value);
	bool isActive();

	void update();

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;

	virtual void onDestroy() {};
	virtual void onEnable() {};
	virtual void onDisable() {};

	virtual void onCollisionEnter(GameObject* pHit) {};
	virtual void onCollisionStay(GameObject* pHit) {};
	virtual void onCollisionExit(GameObject* pHit) {};

	int getUpdateOrder() const;
	GameObject* getUser();

protected:
	AbstractComponent(GameObject* pUser, int updateOrder = 100);

protected:
	GameObject* m_pUser;
	int m_UpdateOrder;
	bool m_Enabled;
	bool m_FirstUpdate;
};

