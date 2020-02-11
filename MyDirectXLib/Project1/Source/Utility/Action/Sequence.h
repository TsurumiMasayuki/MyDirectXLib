#pragma once
#include "AbstractAction.h"
#include <queue>

namespace Action
{
	class Sequence
		: public AbstractAction
	{
	public:
		Sequence(std::queue<AbstractAction*> actionQueue);
		Sequence(int count, AbstractAction* first, ...);
		~Sequence();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual bool isEnd() override;

	private:
		std::queue<AbstractAction*> m_ActionQueue;
		std::queue<AbstractAction*> m_ActionQueueOrigin;
	};
}
