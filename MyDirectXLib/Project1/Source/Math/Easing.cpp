#include "Easing.h"
#include <cmath>

constexpr float PI = 3.1415926545f;			//ƒÎ
constexpr float PI_HALF = 3.1415926545f / 2.0f; //ƒÎ‚Ì“ñ•ª‚Ìˆê

float Easing::easeInSine(float t)
{
	return sinf(PI_HALF * t);
}

float Easing::easeOutSine(float t)
{
	t = t - 1;
	return 1 + sinf(PI_HALF * t);
}

float Easing::easeInOutSine(float t)
{
	return 0.5f * (1 + sinf(PI *  (t - 0.5)));
}

float Easing::easeInQuad(float t)
{
	return t * t;
}

float Easing::easeOutQuad(float t)
{
	return t * (2 - t);
}

float Easing::easeInOutQuad(float t)
{
	return t < 0.5f ? 2 * t * t : t * (4 - 2 * t) - 1;
}

float Easing::easeInCubic(float t)
{
	return t * t * t;
}

float Easing::easeOutCubic(float t)
{
	t = t - 1;
	return 1 + t * t * t;
}

float Easing::easeInOutCubic(float t)
{
	return t < 0.5f ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
}

float Easing::easeInQuart(float t)
{
	t *= t;
	return t * t;
}

float Easing::easeOutQuart(float t)
{
	t = (--t) * t;
	return 1 - t * t;
}

float Easing::easeInOutQuart(float t)
{
	if (t < 0.5f)
	{
		t *= t;
		return 8 * t * t;
	}
	else
	{
		t = (--t) * t;
		return 1 - 8 * t * t;
	}
}

float Easing::easeInQuint(float t)
{
	return powf(t, 5);
}

float Easing::easeOutQuint(float t)
{
	float t2 = (--t) * t;
	return 1 + t * t2 * t2;
}

float Easing::easeInOutQuint(float t)
{
	if (t < 0.5f)
	{
		return 16 * powf(t, 5);
	}
	else
	{
		float t2 = (--t) * t;
		return 1 + 16 * t * t2 * t2;
	}
}

float Easing::easeInExpo(float t)
{
	return (powf(2, 8 * t) - 1) / 255;
}

float Easing::easeOutExpo(float t)
{
	return 1 - powf(2, -8 * t);
}

float Easing::easeInOutExpo(float t)
{
	if (t < 0.5f)
	{
		return (powf(2, 16 * t) - 1) / 510;
	}
	else
	{
		return 1 - 0.5f * powf(2, -16 * (t - 0.5f));
	}
}

float Easing::easeInCirc(float t)
{
	return 1 - sqrtf(1 - t);
}

float Easing::easeOutCirc(float t)
{
	return sqrtf(t);
}

float Easing::easeInOutCirc(float t)
{
	if (t < 0.5f)
	{
		return (1 - sqrtf(1 - 2 * t)) * 0.5f;
	}
	else
	{
		return (1 + sqrtf(2 * t - 1)) * 0.5f;
	}
}
