#include "SimpleMove.h"
#include "Actor\GameObject.h"
#include "Device\Input.h"
#include "Device\GameTime.h"

void SimpleMove::onStart()
{
}

void SimpleMove::onUpdate()
{
	Vec3 move = Input::getLStickValue().toVec3() * speed * GameTime::getDeltaTime();

	m_pUser->setPosition(m_pUser->getPosition() + move);
}
