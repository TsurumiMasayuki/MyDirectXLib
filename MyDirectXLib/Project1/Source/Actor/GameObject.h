#pragma once
#include <vector>
#include <string>
#include "Math/Vec3.h"
#include "Component\ComponentManager.h"

class AbstractComponent;
class IGameMediator;

class GameObject
{
public:
	GameObject(IGameMediator* pGameMediator);
	virtual ~GameObject();

	void objUpdate();
	void addComponent(AbstractComponent* pComponent);
	void removeComponent(AbstractComponent* pComponent);

	bool compareTag(std::string tag);

	void destroy();
	bool isDestroy();

	void onCollisionEnterCallBack(GameObject* pHit);
	void onCollisionStayCallBack(GameObject* pHit);
	void onCollisionExitCallBack(GameObject* pHit);

	IGameMediator* getGameMediator();

	//コンポーネントの取得
	template<typename T>
	T* getComponent();

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

	//座標が変更された時
	virtual void onPositionChanged(const Vec3& currentPos) {};
	//角度が変更された時
	virtual void onAngleChanged(const Vec3& currentAngle) {};
	//サイズが変更された時
	virtual void onSizeChanged(const Vec3& currentSize) {};

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

	ComponentManager* m_pComponentManager;
};

template<typename T>
inline T * GameObject::getComponent()
{
	T* pComponent = m_pComponentManager->getComponent<T>();
	return pComponent;
}
