#pragma once
#include "AbstractAction.h"
#include "Math\Vec3.h"
#include "Utility\Timer.h"

namespace Action
{
	class MoveBy
		: public AbstractAction
	{
	public:
		MoveBy(Vec3 moveValue, float time);
		~MoveBy();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		Vec3 m_Origin;
		Vec3 m_MoveValue;
		Vec3 m_Destination;
		Timer m_MoveTimer;
	};
};