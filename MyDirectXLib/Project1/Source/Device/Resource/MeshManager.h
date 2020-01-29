#pragma once
#include <unordered_map>
#include <string>

struct Mesh;

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void loadMesh(std::string key, std::string filePath);
	Mesh* getMesh(std::string key);

	void unLoadAll();

private:
	//�R�s�[�֎~
	MeshManager(const MeshManager&) = delete;
	void operator = (const MeshManager&) = delete;

private:
	std::unordered_map<std::string, Mesh*> m_Meshes;
};