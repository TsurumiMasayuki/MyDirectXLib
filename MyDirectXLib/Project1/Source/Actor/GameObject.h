#pragma once
#include <vector>
#include <string>
#include "Math/Vec3.h"
#include "Component\ComponentManager.h"

class AbstractComponent;
class IGameMediator;
class Transform;

class GameObject
{
public:
	GameObject(IGameMediator* pGameMediator);
	virtual ~GameObject();

	void objUpdate();
	void addComponent(AbstractComponent* pComponent);
	void removeComponent(AbstractComponent* pComponent);

	void setPosition(Vec3 position);
	Vec3 getPosition();

	void setAngles(Vec3 angles);
	Vec3 getAngles();

	void setSize(Vec3 size);
	Vec3 getSize();

	//�e�I�u�W�F�N�g��ݒ�(nullptr�ŉ���)
	void setParent(GameObject* parent);
	//�e�I�u�W�F�N�g���擾
	GameObject* getParent();

	//�q�I�u�W�F�N�g��o�^
	void addChild(GameObject& child);
	//�q�I�u�W�F�N�g��o�^����
	void removeChild(GameObject& child);
	//�q�I�u�W�F�N�g��S�擾
	const std::vector<GameObject*>& getChildren() const { return m_Children; }

	//�^�O�̔�r
	bool compareTag(std::string tag);

	void destroy();
	bool isDestroy();

	void onCollisionEnterCallBack(GameObject* pHit);
	void onCollisionStayCallBack(GameObject* pHit);
	void onCollisionExitCallBack(GameObject* pHit);

	IGameMediator* getGameMediator();

	Transform* getTransform() { return m_pTransform; };

	//�R���|�[�l���g�̎擾
	template<typename T>
	T* getComponent();

#pragma region getter/setter

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
	bool m_Enabled;
	bool m_DestroyFlag;
	bool m_FirstUpdate;

	std::string m_Tag;

	ComponentManager* m_pComponentManager;

	//�e�I�u�W�F�N�g
	GameObject* m_pParent;
	//�q�I�u�W�F�N�g
	std::vector<GameObject*> m_Children;

	Transform* m_pTransform;
};

template<typename T>
inline T * GameObject::getComponent()
{
	T* pComponent = m_pComponentManager->getComponent<T>();
	return pComponent;
}
