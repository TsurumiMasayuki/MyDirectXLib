#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class RepeatForever :
		public AbstractAction
	{
	public:
		RepeatForever(AbstractAction* pTargetAction);
		~RepeatForever();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

		virtual Action::RepeatForever* clone() override;

	private:
		AbstractAction* m_pTargetAction;
	};
};

