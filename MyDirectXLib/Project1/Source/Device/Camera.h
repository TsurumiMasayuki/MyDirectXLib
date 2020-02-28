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

	//‹–ì * Ë‰e•ÏŠ·‚Ìs—ñ‚ğæ“¾(2D)
	static const DirectX::XMMATRIX& getViewProjMatrix2D();
	//‹–ì * Ë‰e•ÏŠ·‚Ìs—ñ‚ğæ“¾(3D)
	static const DirectX::XMMATRIX& getViewProjMatrix3D();

private:
	static Vec3 position;

	static DirectX::XMMATRIX viewMatrix2D;
	static DirectX::XMMATRIX viewMatrix3D;

	static DirectX::XMMATRIX projMatrix;
	static DirectX::XMMATRIX orthoMatrix;

	Camera();
	~Camera();
};

