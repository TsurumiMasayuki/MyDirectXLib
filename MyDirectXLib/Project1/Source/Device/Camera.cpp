#include "Camera.h"
#include "Def\Screen.h"
#include <DirectXMath.h>
#include "Math\MathUtility.h"

Vec3 Camera::position = Vec3::zero();
DirectX::XMMATRIX Camera::viewMatrix2D;
DirectX::XMMATRIX Camera::viewMatrix3D;
DirectX::XMMATRIX Camera::projMatrix;
DirectX::XMMATRIX Camera::orthoMatrix;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init()
{
	DirectX::XMVECTOR vEyePt;
	DirectX::XMVECTOR vLookatPt;
	DirectX::XMVECTOR vUpVec;

	//2D�p
	//�J�����̍��W
	vEyePt = { position.x, position.y, -10.0f, 0.0f };
	//�J������������W
	vLookatPt = DirectX::XMVectorSet(position.x, position.y, 0.0f, 0.0f);
	//�J�����̉�]�̎�
	vUpVec = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//����s��
	viewMatrix2D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);

	//���s���e�̍s��
	orthoMatrix = DirectX::XMMatrixOrthographicLH(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f / (100.0f - 0.3f), 100.0f);

	//3D�p
	//�J�����̍��W
	position.z = -10.0f;
	vEyePt = { position.x, position.y, position.z, 0.0f };
	//�J������������W
	vLookatPt = { 0.0f, 0.0f, 0.0f, 1.0f };
	//�J�����̉�]�̎�
	vUpVec = { 0.0f, 1.0f, 0.0f, 0.0f };
	//����s��
	viewMatrix3D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);

	//����p
	const float fov = 60.0f;
	//�A�X�y�N�g��
	const float aspect = (float)Screen::getWindowWidth() / (float)Screen::getWindowHeight();

	//�������e�̍s��
	projMatrix = DirectX::XMMatrixPerspectiveFovLH(MathUtility::toRadian(fov), aspect, 0.01f, 500.0f);
}

void Camera::update()
{
	//2D�p
	//�J�����̍��W
	DirectX::XMVECTOR vEyePt = { position.x, position.y, -10.0f, 0.0f };
	//�J������������W
	DirectX::XMVECTOR vLookatPt = DirectX::XMVectorSet(position.x, position.y, 0.0f, 0.0f);
	//�J�����̉�]�̎�
	DirectX::XMVECTOR vUpVec = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//����s��
	viewMatrix2D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);

	//3D�p
	//�J�����̍��W
	DirectX::XMVECTOR vEyePt3D = { position.x, position.y, position.z, 0.0f };
	//�J������������W
	DirectX::XMVECTOR vLookatPt3D = DirectX::XMVectorSet(position.x, position.y, 0.0f, 0.0f);
	//�J�����̉�]�̎�
	DirectX::XMVECTOR vUpVec3D = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//����s��
	viewMatrix3D = DirectX::XMMatrixLookAtLH(vEyePt3D, vLookatPt3D, vUpVec3D);

}

void Camera::reset()
{
	position = Vec3::zero();
}

void Camera::setPosition(Vec3 position)
{
	position = position;
}

Vec3 Camera::getPosition()
{
	return position;
}

const DirectX::XMMATRIX& Camera::getViewProjMatrix2D()
{
	return viewMatrix2D * orthoMatrix;
}

const DirectX::XMMATRIX& Camera::getViewProjMatrix3D()
{
	return viewMatrix3D * projMatrix;
}
