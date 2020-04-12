#ifndef _IPOSTEFFECTRENDERER_H_
#define _IPOSTEFFECTRENDERER_H_
#include "Component\Graphics\GraphicsLayer.h"

class IPostEffectRenderer
{
public:
	virtual ~IPostEffectRenderer() {};

	virtual int getDrawOrder() const = 0;
	virtual GraphicsLayer getDestLayer() const = 0;

	virtual void draw() = 0;

protected:
	IPostEffectRenderer() {};
};

#endif // !_IPOSTEFFECTRENDERER_H_
