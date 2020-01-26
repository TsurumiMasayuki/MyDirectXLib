#include "GameDevice.h"

#include <cassert>

#include "Device\Camera.h"
#include "Device\Renderer.h"
#include "Device\Resource\MeshManager.h"
#include "Device\Input.h"

GameDevice* GameDevice::instance = nullptr;

void GameDevice::initialize()
{
	instance = new GameDevice();
	instance->m_pRenderer->init();
	Camera::init();
}

void GameDevice::update()
{
	Camera::update();
	Input::update();
}

void GameDevice::shutdown()
{
	delete instance;
}

Renderer * GameDevice::getRenderer()
{
#ifdef _DEBUG
	assert(instance != nullptr);
#endif

	return instance->m_pRenderer;
}

MeshManager * GameDevice::getMeshManager()
{
#ifdef _DEBUG
	assert(instance != nullptr);
#endif

	return instance->m_pMeshManager;
}

GameDevice::GameDevice()
	:m_pRenderer(new Renderer()),
	m_pMeshManager(new MeshManager())
{
}

GameDevice::~GameDevice()
{
	delete m_pRenderer;
	delete m_pMeshManager;
}
