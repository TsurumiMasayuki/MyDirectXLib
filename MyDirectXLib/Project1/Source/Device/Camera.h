#pragma once
#include "Math\Vec3.h"

namespace DirectX
{
	struct XMMATRIX;
}

class Camera
{
public:
	static void init();
	static void update();
	static void reset();

	static void setPosition(Vec3 position);
	static Vec3 getPosition();

	//Šp“x‚ð•t‚¯‚ç‚ê‚é‚æ‚¤‚É‚·‚é

	static DirectX::XMMATRIX getViewProjMatrix();
	static DirectX::XMMATRIX getViewOrthoMatrix();

private:
	static Vec3 m_Position;

	static DirectX::XMMATRIX viewMatrix2D;
	static DirectX::XMMATRIX viewMatrix3D;

	static DirectX::XMMATRIX projMatrix;
	static DirectX::XMMATRIX orthoMatrix;

	Camera();
	~Camera();
};

