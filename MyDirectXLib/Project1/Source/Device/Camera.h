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

	//視野 * 射影変換の行列を取得(2D)
	static const DirectX::XMMATRIX& getViewProjMatrix2D();
	//視野 * 射影変換の行列を取得(3D)
	static const DirectX::XMMATRIX& getViewProjMatrix3D();

	//画面外のオブジェクトかどうかを判定する
	static bool isCulling2D(const Vec3& position, const Vec3& size);

private:
	static Vec3 position;

	static DirectX::XMMATRIX viewMatrix2D;
	static DirectX::XMMATRIX viewMatrix3D;

	static DirectX::XMMATRIX projMatrix;
	static DirectX::XMMATRIX orthoMatrix;

	Camera();
	~Camera();
};

