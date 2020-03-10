#pragma once
#include "Math\Vec3.h"

class GameObject;

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

	//�Փ˔���p�֐�(�����R���|�[�l���g�ł̂ݎg�p)
	virtual void checkCollision2D() {};

	//�Փ˔���p�֐�(�����R���|�[�l���g�ł̂ݎg�p)
	virtual void checkCollision3D() {};

	virtual void onCollisionEnter(GameObject* pHit) {};
	virtual void onCollisionStay(GameObject* pHit) {};
	virtual void onCollisionExit(GameObject* pHit) {};

	int getUpdateOrder() const;
	GameObject* getUser();

	void setPosition(const Vec3& position);
	Vec3 getPosition() const;

	void setAngles(const Vec3& angles);
	Vec3 getAngles() const;

	void setSize(const Vec3& size);
	Vec3 getSize() const;

protected:
	AbstractComponent(GameObject* pUser, int updateOrder = 100);

private:
	//�R�s�[�֎~
	AbstractComponent(const AbstractComponent&) = delete;
	AbstractComponent& operator = (const AbstractComponent&) = delete;

protected:
	GameObject* m_pUser;
	int m_UpdateOrder;
	bool m_Enabled;
	bool m_FirstUpdate;
};

