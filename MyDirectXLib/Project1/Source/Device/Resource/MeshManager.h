#pragma once
#include <unordered_map>
#include <string>

struct Mesh;

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void loadMesh(std::string key, const std::string filePath, const std::wstring textureName = L"Default");
	Mesh* getMesh(std::string key);

	void unLoadAll();

private:
	//ƒRƒs[‹Ö~
	MeshManager(const MeshManager&) = delete;
	void operator = (const MeshManager&) = delete;

private:
	std::unordered_map<std::string, Mesh*> m_Meshes;
};