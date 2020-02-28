#pragma once

class IRenderer2D
{
public:
	virtual ~IRenderer2D() {};

	virtual int getDrawOrder() const = 0;
	virtual void draw() = 0;

protected:
	IRenderer2D() {};
};