#ifndef _IRENDERER2D_H_
#define _IRENDERER2D_H_

#include "GraphicsLayer.h"

class IRenderer2D
{
public:
	virtual ~IRenderer2D() {};

	virtual int getDrawOrder() const = 0;
	virtual GraphicsLayer getGraphicsLayer() const = 0;

	virtual void draw() = 0;

protected:
	IRenderer2D() {};
};

#endif // !_IRENDERER2D_H_
