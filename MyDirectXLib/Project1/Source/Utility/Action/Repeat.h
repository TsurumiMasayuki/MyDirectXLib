#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class Repeat :
		public AbstractAction
	{
	public:
		Repeat(AbstractAction* pTargetAction, int repeatCount);
		~Repeat();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;
		virtual Action::Repeat* clone() override;

	private:
		int m_RepeatCount;
		int m_RepeatCountOrigin;
		AbstractAction* m_pTargetAction;
	};
};

