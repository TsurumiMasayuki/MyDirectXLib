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

float Easing::easeInBack(float t)
{
	return t * t * (2.70158f * t - 1.70158f);
}

float Easing::easeOutBack(float t)
{
	return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

float Easing::easeInOutBack(float t)
{
	if (t < 0.5f)
	{
		return t * t * (7 * t - 2.5f) * 2;
	}
	else
	{
		return 1 + (--t) * t * 2 * (7 * t + 2.5f);
	}
}

float Easing::easeInElastic(float t)
{
	return powf(t, 4) * sinf(t * PI * 4.5f);
}

float Easing::easeOutElastic(float t)
{
	return 1 - powf(t - 1, 4) * cosf(t * PI * 4.5f);
}

float Easing::easeInOutElastic(float t)
{
	if (t < 0.45f)
	{
		return 8 * powf(t, 4) * sinf(t * PI * 9);
	}
	else if (t < 0.55f)
	{
		return 0.5f + 0.75f * sinf(t * PI * 4);
	}
	else
	{
		return 1 - 8 * powf(t - 1, 4) * sinf(t * PI * 9);
	}
}

float Easing::easeInBounce(float t)
{
	return powf(2, 6 * (t - 1)) * fabsf(sinf(t * PI * 3.5f));
}

float Easing::easeOutBounce(float t)
{
	return 1 - powf(2, -6 * t) * fabsf(cosf(t * PI * 3.5f));
}

float Easing::easeInOutBounce(float t)
{
	if (t < 0.5f)
	{
		return 8 * powf(2, 8 * (t - 1)) * fabsf(sinf(t * PI * 7));
	}
	else
	{
		return 1 - 8 * powf(2, -8 * t) * fabsf(sinf(t * PI * 7));
	}
}
