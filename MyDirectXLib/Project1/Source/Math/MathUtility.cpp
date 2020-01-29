#include "MathUtility.h"
#include <math.h>
#include <DirectXMath.h>

float MathUtility::clamp(const float value, const float min, const float max)
{
	return fmaxf(min, fminf(max, value));
}

float MathUtility::lerp(const float current, const float target, const float t)
{
	float clampT = clamp(t, 0.0f, 1.0f);
	float result = (1 - clampT) * current + clampT * target;
	return result;
}

float MathUtility::repeat(const float current, const float length)
{
	float result = fmodf(current, length);
	return result;
}

float MathUtility::moveTowards(const float current, const float target, const float delta)
{
	float result = moveTowardsNoClamp(current, target, delta);
	
	if (target < 0)
		result = fmaxf(result, target);
	else
		result = fminf(result, target);

	return result;
}

float MathUtility::moveTowardsNoClamp(const float current, const float target, const float delta)
{
	float result = current + (target - current) * delta;

	return result;
}

float MathUtility::toRadian(float degree)
{
	return DirectX::XMConvertToRadians(degree);
}

float MathUtility::toDegree(float radian)
{
	return DirectX::XMConvertToDegrees(radian);
}

float MathUtility::distance(float x1, float y1, float x2, float y2)
{
	float a = fabsf(x1 - x2);
	float b = fabsf(y1 - y2);

	return sqrtf(a * a + b * b);
}

float MathUtility::sign(float value)
{
	if (value > 0.0f)
		return 1.0f;
	
	if (value < 0.0f)
		return -1.0f;

	return 0.0f;
}

bool MathUtility::isInRange(const float compareValue, const float value1, const float value2)
{
	float min = fminf(value1, value2);
	float max = fmaxf(value1, value2);

	return compareValue >= min && compareValue <= max;
}
