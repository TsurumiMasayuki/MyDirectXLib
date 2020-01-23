#include "RectF.h"

RectF::RectF()
	: RectF(0, 0, 0, 0)
{
}

RectF::RectF(float x, float y, float width, float height)
	: x(x), y(y), width(width), height(height)
{
}

RectF::~RectF()
{
}
