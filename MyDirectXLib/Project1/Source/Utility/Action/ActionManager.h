#pragma once
#include <queue>

class GameObject;
namespace Action
{
	class AbstractAction;

	class ActionManager
	{
	public:
		ActionManager(GameObject* pUser);
		~ActionManager();

		void update();
		void enqueueAction(AbstractAction* action);
		void forceNext();
		int actionCount();

	private:
		void actionChange();

	private:
		std::queue<AbstractAction*> m_ActionQueue;
		GameObject* m_pUser;
	};
};