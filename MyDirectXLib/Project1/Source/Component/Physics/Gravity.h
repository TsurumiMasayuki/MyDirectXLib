#pragma once
#include "Component\AbstractComponent.h"

class Gravity
	: public AbstractComponent
{
public:
	Gravity(GameObject* pUser, float mass = 1.0f);
	~Gravity();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual TypeID getType() const override;

	virtual void onDestroy() override;

	float getGravSpeed();
	bool isGround();

private:
	class GroundDetector
		: public AbstractComponent
	{
	public:
		GroundDetector(GameObject* pUser, Gravity* pListner);

		virtual void onStart() override;
		virtual void onUpdate() override;
		virtual TypeID getType() const override;

		virtual void onCollisionEnter(GameObject* pHit) override;
		virtual void onCollisionStay(GameObject* pHit) override;
		virtual void onCollisionExit(GameObject* pHit) override;

	private:
		Gravity* m_pListner;

	};

	static const float GRAVITY_ACC;

	GameObject* m_pGroundDetector;

	float m_Mass;
	float m_GravSpeed;
	float m_DetectorDistance;
	bool m_isGround;
};