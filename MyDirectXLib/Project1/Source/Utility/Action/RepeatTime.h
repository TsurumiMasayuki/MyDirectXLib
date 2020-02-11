#pragma once
#include "AbstractAction.h"

namespace Action
{
	class RepeatTime :
		public AbstractAction
	{
	public:
		RepeatTime(AbstractAction* pAction, float repeatTime);
		~RepeatTime();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;

	private:
		AbstractAction* m_pAction;
	};
};

