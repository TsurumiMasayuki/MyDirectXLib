#pragma once
#include <queue>
#include "AbstractComponent.h"

class GameObject;

namespace Action
{
	class AbstractAction;

	class ActionManager
		: public AbstractComponent
	{
	public:
		ActionManager(GameObject* pUser);
		~ActionManager();

		virtual void onStart() override;
		virtual void onUpdate() override;

		void enqueueAction(AbstractAction* action);
		void forceNext();
		int actionCount();

	private:
		void actionChange();

	private:
		std::queue<AbstractAction*> m_ActionQueue;
	};
}