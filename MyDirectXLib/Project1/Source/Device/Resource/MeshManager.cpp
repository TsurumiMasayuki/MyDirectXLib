#include "MeshManager.h"
#include "Device\Resource\Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	unLoadAll();
}

void MeshManager::loadMesh(std::string key, std::string filePath)
{
	auto pMesh = new Mesh();
	pMesh->init(filePath.c_str());
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
