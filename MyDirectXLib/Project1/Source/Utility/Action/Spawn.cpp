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
		action->init();
	}
}

void Action::Spawn::update()
{
	for (auto action : m_ActionList)
	{
		if (!action->isEnd())
			action->update();
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
