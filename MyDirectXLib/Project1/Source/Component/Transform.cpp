#include "Transform.h"
#include "Actor\GameObject.h"
#include <DirectXMath.h>
#include "Math\MathUtility.h"

Transform::Transform(GameObject * pUser)
	: AbstractComponent(pUser),
	m_Position(Vec3::zero()),
	m_Angles(Vec3::zero()),
	m_Size(Vec3(1, 1, 1)),
	m_LocalPosition(Vec3::zero()),
	m_LocalAngles(Vec3::zero())
{
}

Transform::~Transform()
{
}

void Transform::setPosition(Vec3 position)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//親が無かったらそのまま設定
		m_LocalPosition = position;
	else
		//そうでない場合は親基準で設定
		m_LocalPosition = position - parent->getTransform()->getPosition();

	//座標を設定
	m_Position = position;

	auto children = *getUser()->getChildren();

	//子オブジェクトに座標を適用
	for (auto child : children)
	{
		child->getTransform()->updatePosition();
	}
}

void Transform::setAngleZ(float angle)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//親が無かったらそのまま設定
		m_LocalAngles.z = angle;
	else
		//そうでない場合は親基準で設定
		m_LocalAngles.z = angle - parent->getTransform()->getLocalAngleZ();

	//座標を設定
	m_Angles.z = angle;

	auto children = *getUser()->getChildren();

	//子オブジェクトに座標を適用
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setAngles(Vec3 angles)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//親が無かったらそのまま設定
		m_LocalAngles = angles;
	else
		//そうでない場合は親基準で設定
		m_LocalAngles = angles - parent->getTransform()->getLocalAngles();

	//座標を設定
	m_Angles = angles;

	auto children = *getUser()->getChildren();

	//子オブジェクトに座標を適用
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setLocalPosition(Vec3 position)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//親が無かったらそのまま設定
		m_Position = position;
	else
		//そうでない場合は親基準で設定
		m_Position = position + parent->getTransform()->getPosition();

	//ローカル座標を設定
	m_LocalPosition = position;

	//子に座標を適用
	auto children = *getUser()->getChildren();
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setLocalAngleZ(float angle)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//親が無かったらそのまま設定
		m_Angles.z = angle;
	else
		//そうでない場合は親基準で設定
		m_Angles.z = angle + parent->getTransform()->getAngleZ();

	//ローカル座標を設定
	m_LocalAngles.z = angle;

	//子に座標を適用
	auto children = *getUser()->getChildren();
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setLocalAngles(Vec3 angles)
{
	m_LocalAngles = angles;
}

DirectX::XMMATRIX Transform::getWorldMatrix()
{
	//移動
	DirectX::XMMATRIX translate = DirectX::XMMatrixTranslationFromVector(m_pUser->getTransform()->getPosition().toXMVector());

	//角度をラジアンに変換
	Vec3 radRotation = getAngles();
	radRotation.x = MathUtility::toRadian(radRotation.x);
	radRotation.y = MathUtility::toRadian(radRotation.y);
	radRotation.z = MathUtility::toRadian(radRotation.z);

	//回転
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYawFromVector(radRotation.toXMVector());
	//拡大縮小
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScalingFromVector(m_pUser->getTransform()->getSize().toXMVector());
	//ワールド行列作成
	DirectX::XMMATRIX world = scaling * rotation * translate;

	return world;
}

void Transform::updatePosition()
{
	auto parent = m_pUser->getParent();
	m_Position = parent->getTransform()->getPosition() + m_LocalPosition;
}

void Transform::updateAngles()
{
	auto parent = m_pUser->getParent();
	m_Angles = parent->getTransform()->getAngles() + m_LocalAngles;
}
