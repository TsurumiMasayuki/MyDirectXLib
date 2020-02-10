#pragma once
#include "AbstractAction.h"
#include "Math\Vec3.h"
#include "Utility\Timer.h"

namespace Action
{
	class MoveTo
		: public AbstractAction
	{
	public:
		MoveTo(GameObject* pUser, Vec3 destination, float time);
		~MoveTo();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		Vec3 m_Origin;
		Vec3 m_Destination;
		Timer m_MoveTimer;
	};
};