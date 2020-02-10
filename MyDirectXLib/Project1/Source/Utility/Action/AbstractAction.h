#pragma once

class GameObject;

namespace Action
{
	class AbstractAction
	{
	public:
		AbstractAction() : m_pUser(nullptr) {};
		virtual ~AbstractAction() {};

		void baseInit(GameObject* pUser) { m_pUser = pUser; }

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void onSuspend() = 0;
		virtual bool isEnd() = 0;

	protected:
		GameObject* m_pUser;
	};
};