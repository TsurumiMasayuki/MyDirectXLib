#pragma once
class GameObject;
class RenderManager;
struct Vec3;

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

	//衝突判定用関数(物理コンポーネントでのみ使用)
	virtual void checkCollision2D() {};

	//衝突判定用関数(物理コンポーネントでのみ使用)
	virtual void checkCollision3D() {};

	virtual void onCollisionEnter(GameObject* pHit) {};
	virtual void onCollisionStay(GameObject* pHit) {};
	virtual void onCollisionExit(GameObject* pHit) {};

	//座標が変更された時
	virtual void onPositionChanged(const Vec3& currentPos) {};
	//角度が変更された時
	virtual void onAngleChanged(const Vec3& currentAngle) {};
	//サイズが変更された時
	virtual void onSizeChanged(const Vec3& currentSize) {};

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

