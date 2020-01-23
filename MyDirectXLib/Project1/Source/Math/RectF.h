#pragma once

struct RectF
{
public:
	RectF();
	RectF(float x, float y, float width, float height);
	~RectF();

public:
	float x;
	float y;
	float width;
	float height;
};