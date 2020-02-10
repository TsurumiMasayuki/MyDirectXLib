#pragma once
#include "AbstractAction.h"
#include "Utility\Timer.h"

namespace Action
{
	class Repeat :
		public AbstractAction
	{
	public:
		Repeat(AbstractAction* pAction, int repeatCount);
		~Repeat();

		virtual void init() override;
		virtual void update() override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		int m_RepeatCount;
		int m_RepeatCountOrigin;
		AbstractAction* m_pAction;
	};
};

