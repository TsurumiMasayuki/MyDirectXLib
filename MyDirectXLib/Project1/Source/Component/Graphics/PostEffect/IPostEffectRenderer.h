#ifndef _IPOSTEFFECTRENDERER_H_
#define _IPOSTEFFECTRENDERER_H_
#include "Component\Graphics\GraphicsLayer.h"

class IPostEffectRenderer
{
public:
	virtual ~IPostEffectRenderer() {};

	virtual void draw() = 0;

protected:
	IPostEffectRenderer() {};
};

#endif // !_IPOSTEFFECTRENDERER_H_
