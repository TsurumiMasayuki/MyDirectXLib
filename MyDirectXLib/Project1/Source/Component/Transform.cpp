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
		//�e�����������炻�̂܂ܐݒ�
		m_LocalPosition = position;
	else
		//�����łȂ��ꍇ�͐e��Őݒ�
		m_LocalPosition = position - parent->getTransform()->getPosition();

	//���W��ݒ�
	m_Position = position;

	auto children = *getUser()->getChildren();

	//�q�I�u�W�F�N�g�ɍ��W��K�p
	for (auto child : children)
	{
		child->getTransform()->updatePosition();
	}
}

void Transform::setAngleZ(float angle)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//�e�����������炻�̂܂ܐݒ�
		m_LocalAngles.z = angle;
	else
		//�����łȂ��ꍇ�͐e��Őݒ�
		m_LocalAngles.z = angle - parent->getTransform()->getLocalAngleZ();

	//���W��ݒ�
	m_Angles.z = angle;

	auto children = *getUser()->getChildren();

	//�q�I�u�W�F�N�g�ɍ��W��K�p
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setAngles(Vec3 angles)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//�e�����������炻�̂܂ܐݒ�
		m_LocalAngles = angles;
	else
		//�����łȂ��ꍇ�͐e��Őݒ�
		m_LocalAngles = angles - parent->getTransform()->getLocalAngles();

	//���W��ݒ�
	m_Angles = angles;

	auto children = *getUser()->getChildren();

	//�q�I�u�W�F�N�g�ɍ��W��K�p
	for (auto child : children)
	{
		child->getTransform()->updateAngles();
	}
}

void Transform::setLocalPosition(Vec3 position)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//�e�����������炻�̂܂ܐݒ�
		m_Position = position;
	else
		//�����łȂ��ꍇ�͐e��Őݒ�
		m_Position = position + parent->getTransform()->getPosition();

	//���[�J�����W��ݒ�
	m_LocalPosition = position;

	//�q�ɍ��W��K�p
	auto children = *getUser()->getChildren();
	for (auto child : children)
	{
		child->getTransform()->updatePosition();
	}
}

void Transform::setLocalAngleZ(float angle)
{
	auto parent = m_pUser->getParent();
	if (parent == nullptr)
		//�e�����������炻�̂܂ܐݒ�
		m_Angles.z = angle;
	else
		//�����łȂ��ꍇ�͐e��Őݒ�
		m_Angles.z = angle + parent->getTransform()->getAngleZ();

	//���[�J�����W��ݒ�
	m_LocalAngles.z = angle;

	//�q�ɍ��W��K�p
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
	//�ړ�
	DirectX::XMMATRIX translate = DirectX::XMMatrixTranslationFromVector(m_pUser->getTransform()->getPosition().toXMVector());

	//�p�x�����W�A���ɕϊ�
	Vec3 radRotation = getAngles();
	radRotation.x = MathUtility::toRadian(radRotation.x);
	radRotation.y = MathUtility::toRadian(radRotation.y);
	radRotation.z = MathUtility::toRadian(radRotation.z);

	//��]
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYawFromVector(radRotation.toXMVector());
	//�g��k��
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScalingFromVector(m_pUser->getTransform()->getSize().toXMVector());
	//���[���h�s��쐬
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
