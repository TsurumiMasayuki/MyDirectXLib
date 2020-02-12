#include "Spawn.h"
#include <stdarg.h>

Action::Spawn::Spawn(std::vector<AbstractAction*> actionList)
{
	m_ActionList.reserve(actionList.size());
	std::copy(actionList.begin(), actionList.end(), m_ActionList.begin());
}

Action::Spawn::Spawn(int count, AbstractAction * first, ...)
{
	m_ActionList.reserve(count);
	m_ActionList.emplace_back(first);

	va_list args;
	va_start(args, first);
	for (int i = 0; i < count - 1; i++)
	{
		m_ActionList.emplace_back(va_arg(args, AbstractAction*));
	}
	va_end(args);
}

Action::Spawn::~Spawn()
{
	for (auto action : m_ActionList)
	{
		delete action;
	}
	m_ActionList.clear();
	m_ActionList.shrink_to_fit();
}

void Action::Spawn::init()
{
	for (auto action : m_ActionList)
	{
		action->setUser(m_pUser);
		action->baseInit();
	}
}

void Action::Spawn::update(float time)
{
	for (auto action : m_ActionList)
	{
		if (!action->isEnd())
			action->baseUpdate();
	}
}

void Action::Spawn::onSuspend()
{
	for (auto action : m_ActionList)
	{
		action->onSuspend();
	}
}

bool Action::Spawn::isEnd()
{
	for (auto action : m_ActionList)
	{
		if (!action->isEnd())
			return false;
	}

	return true;
}

Action::Spawn * Action::Spawn::clone()
{
	std::vector<AbstractAction*> cloneVector;
	cloneVector.reserve(m_ActionList.size());

	for (int i = 0; i < m_ActionList.size(); ++i)
	{
		cloneVector.at(i) = m_ActionList.at(i)->clone();
	}

	return new Spawn(cloneVector);
}
