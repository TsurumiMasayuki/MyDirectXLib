#include "MeshManager.h"
#include "Device\Resource\Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	unLoadAll();
}

void MeshManager::loadMesh(const std::string key, const std::string filePath, const std::wstring textureName)
{
	auto pMesh = new Mesh();
	pMesh->init(filePath, textureName);
	m_Meshes.emplace(key, pMesh);
}

Mesh * MeshManager::getMesh(std::string key)
{
	return m_Meshes.at(key);
}

void MeshManager::unLoadAll()
{
	for (auto mesh : m_Meshes)
	{
		delete mesh.second;
	}
}
