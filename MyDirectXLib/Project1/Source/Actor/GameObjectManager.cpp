#include "GameObjectManager.h"

#include <unordered_set>

#include "GameObject.h"
#include "Def/ManagerConfig.h"

GameObjectManager::GameObjectManager()
{
	m_GameObjects.reserve(ManagerConfig::GameObjectReserve);
}

GameObjectManager::~GameObjectManager()
{
	while (!m_AddObjects.empty())
	{
		delete m_AddObjects.back();
	}

	m_AddObjects.clear();

	while (!m_GameObjects.empty())
	{
		delete m_GameObjects.back();
	}

	m_GameObjects.clear();
}

void GameObjectManager::update()
{
	addObjects();

	for (auto& gameObject : m_AddObjects)
	{
		if (!gameObject->isActive()) continue;

		gameObject->objUpdate();
	}

	for (auto& gameObject : m_GameObjects)
	{
		if (!gameObject->isActive()) continue;

		gameObject->objUpdate();
	}

	destroyObjects();
}

void GameObjectManager::add(GameObject * pGameObject)
{
	m_AddObjects.emplace_back(pGameObject);
}

void GameObjectManager::remove(GameObject * pGameObject)
{
	//�����ɍ폜�Ώۂ��ړ�����popback
	auto itr = std::find(m_AddObjects.begin(), m_AddObjects.end(), pGameObject);
	if (itr != m_AddObjects.end())
	{
		std::iter_swap(itr, m_AddObjects.end() - 1);
		m_AddObjects.pop_back();
	}

	//�����ɍ폜�Ώۂ��ړ�����popback
	itr = std::find(m_GameObjects.begin(), m_GameObjects.end(), pGameObject);
	if (itr != m_GameObjects.end())
	{
		std::iter_swap(itr, m_GameObjects.end() - 1);
		m_GameObjects.pop_back();
	}
}

void GameObjectManager::addObjects()
{
	if (m_AddObjects.size() == 0)
		return;

	std::copy(m_AddObjects.begin(), m_AddObjects.end(), std::back_inserter(m_GameObjects));
	m_AddObjects.clear();
	m_AddObjects.shrink_to_fit();
}

void GameObjectManager::destroyObjects()
{
	//�d�����ē�d�폜�ɂȂ�̂�h�~����
	std::unordered_set<GameObject*> destroyList;
	for (auto gameObject : m_GameObjects)
	{
		if (gameObject->isDestroy())
			destroyList.emplace(gameObject);
	}

	for (auto gameObject : m_AddObjects)
	{
		if (gameObject->isDestroy())
			destroyList.emplace(gameObject);
	}

	for (auto destroy : destroyList)
	{
		delete destroy;
	}

	destroyList.clear();

	m_GameObjects.shrink_to_fit();
}
