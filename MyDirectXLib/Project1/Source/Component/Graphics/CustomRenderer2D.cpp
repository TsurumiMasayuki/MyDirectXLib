#include "CustomRenderer2D.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Device\Camera.h"
#include "Device\DirectXManager.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"
#include "Device\Resource\TextureManager.h"
#include "Device\Resource\Shader\ShaderManager.h"

#include "Device\Buffer\ConstantBuffer.h"

#include "Actor\GameObject.h"
#include "Component\Transform.h"

CustomRenderer2D::CustomRenderer2D(GameObject * pUser, int drawOrder)
	: AbstractComponent(pUser), m_DrawOrder(drawOrder)
{
	GameDevice::getRenderer()->addRenderer2D(this);
}

CustomRenderer2D::~CustomRenderer2D()
{
	GameDevice::getRenderer()->removeRenderer2D(this);
}

void CustomRenderer2D::onStart()
{

}

void CustomRenderer2D::onUpdate()
{
}

int CustomRenderer2D::getDrawOrder() const
{
	return m_DrawOrder;
}

GraphicsLayer CustomRenderer2D::getGraphicsLayer() const
{
	return m_GraphicsLayer;
}

void CustomRenderer2D::draw()
{
	if (!isActive()) return;

	//頂点シェーダーとピクセルシェーダーが揃っていない場合何もしない
	if (m_pVertexShader != nullptr &&
		m_pPixelShader != nullptr) 
		return;
}

void CustomRenderer2D::setVertexShader(const std::string & shaderName)
{
	m_pVertexShader = ShaderManager::GetVertexShader(shaderName);
}

void CustomRenderer2D::setPixelShader(const std::string & shaderName)
{
	m_pPixelShader = ShaderManager::GetPixelShader(shaderName);
}
