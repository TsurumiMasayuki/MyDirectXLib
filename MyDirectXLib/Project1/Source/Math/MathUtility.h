#pragma once

namespace MathUtility
{
	float clamp(const float value, const float min, const float max);
	float lerp(const float current, const float target, const float t);
	float repeat(const float current, const float length);
	float moveTowards(const float current, const float target, const float delta);
	float moveTowardsNoClamp(const float current, const float target, const float delta);
	float toRadian(float degree);
	float toDegree(float radian);
	float distance(float x1, float y1, float x2, float y2);
	float sign(float value);

	bool isInRange(const float compareValue, const float min, const float max);
};

