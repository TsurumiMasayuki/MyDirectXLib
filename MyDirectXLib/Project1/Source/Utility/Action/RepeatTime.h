#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class RepeatTime :
		public AbstractAction
	{
	public:
		RepeatTime(AbstractAction* pAction, float repeatTime);
		~RepeatTime();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		Timer m_Timer;
		AbstractAction* m_pAction;
	};
};

