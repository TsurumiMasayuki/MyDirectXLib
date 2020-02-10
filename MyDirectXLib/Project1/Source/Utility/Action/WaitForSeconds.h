#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class WaitForSeconds
		: public AbstractAction
	{
	public:
		WaitForSeconds(float waitTime);
		~WaitForSeconds();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		Timer m_Timer;
	};
}