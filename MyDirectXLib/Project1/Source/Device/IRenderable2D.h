#pragma once

class Renderer;

class IRenderable2D
{
public:
	IRenderable2D() {};
	virtual ~IRenderable2D() {};

	virtual int getDrawOrder2D() = 0;
	virtual void draw2D(Renderer* pRenderer) = 0;
};