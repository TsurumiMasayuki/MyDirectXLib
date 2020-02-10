#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class RepeatForever :
		public AbstractAction
	{
	public:
		RepeatForever(AbstractAction* pAction);
		~RepeatForever();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		AbstractAction* m_pAction;
	};
};

