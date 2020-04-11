#include "SpriteRenderer.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "Device\Camera.h"
#include "Device\DirectXManager.h"
#include "Device\GameDevice.h"
#include "Device\Renderer.h"
#include "Device\Resource\TextureManager.h"
#include "Device\Resource\Shader\ShaderManager.h"
#include "Device\Resource\Shader\VertexShader.h"
#include "Device\Resource\Shader\PixelShader.h"

#include "Device\Base\SpriteVertex.h"

#include "Device\Buffer\VertexBuffer.h"
#include "Device\Buffer\IndexBuffer.h"
#include "Device\Buffer\SpriteConstantBuffer.h"
#include "Device\Buffer\ConstantBuffer.h"

#include "Actor\GameObject.h"
#include "Component\Transform.h"

using namespace DirectX;

int SpriteRenderer::componentCount;

ID3D11InputLayout* SpriteRenderer::pInputLayout;
ID3D11SamplerState* SpriteRenderer::pSampler;

VertexBuffer* SpriteRenderer::pVertices;
IndexBuffer* SpriteRenderer::pIndices;
ConstantBuffer* SpriteRenderer::pSpriteCB;

SpriteRenderer::SpriteRenderer(GameObject * pUser, int drawOrder)
	: AbstractComponent(pUser),
	m_DrawOrder(drawOrder),
	m_pVertexShader(nullptr),
	m_pPixelShader(nullptr),
	m_pSRV(nullptr),
	m_Color(DirectX::Colors::White),
	m_UVRect(0, 0, 1, 1),
	m_ImagePivot(0, 0),
	m_GraphicsLayer(GraphicsLayer::Final)
{
	//Renderer�ɓo�^
	GameDevice::getRenderer()->addRenderer2D(this);

	//���_�V�F�[�_�[�擾
	m_pVertexShader = ShaderManager::GetVertexShader("SpriteVS");
	//�s�N�Z���V�F�[�_�[�擾
	m_pPixelShader = ShaderManager::GetPixelShader("SpritePS");

	if (componentCount == 0)
	{
		auto pDevice = DirectXManager::getDevice();

		//InputLayout�쐬
		D3D11_INPUT_ELEMENT_DESC inputDesc[2];
		SpriteVertex::getInputDesc(inputDesc);
		UINT numElements = 2;

		m_pVertexShader->createInputLayout(
			pDevice,
			inputDesc,
			2,
			&pInputLayout
		);

		//SamplerState�쐬
		D3D11_SAMPLER_DESC spriteSamDesc;
		ZeroMemory(&spriteSamDesc, sizeof(D3D11_SAMPLER_DESC));
		spriteSamDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		spriteSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		spriteSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		spriteSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		spriteSamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		pDevice->CreateSamplerState(&spriteSamDesc, &pSampler);

		//���_�o�b�t�@�쐬
		float width = 0.5f;
		float height = 0.5f;

		//�l�p�̒��_���쐬
		SpriteVertex vertices[]
		{
			{{-width,  height, 0.0f}, {0.0f, 0.0f}},
			{{ width, -height, 0.0f}, {1.0f, 1.0f}},
			{{-width, -height, 0.0f}, {0.0f, 1.0f}},
			{{ width,  height, 0.0f}, {1.0f, 0.0f}},
		};

		pVertices = new VertexBuffer();
		pVertices->init(pDevice, sizeof(SpriteVertex) * 4, vertices);

		UINT indices[]
		{
			0, 1, 2,
			0, 3, 1
		};

		pIndices = new IndexBuffer();
		pIndices->init(pDevice, sizeof(UINT) * 6, indices);

		//�R���X�^���g�o�b�t�@�쐬
		pSpriteCB = new ConstantBuffer();
		SpriteConstantBuffer buffer;
		pSpriteCB->init(DirectXManager::getDevice(), sizeof(SpriteConstantBuffer), &buffer);
	}

	componentCount++;
}

SpriteRenderer::~SpriteRenderer()
{
	//Renderer����폜
	GameDevice::getRenderer()->removeRenderer2D(this);

	componentCount--;

	if (componentCount == 0)
	{
		pInputLayout->Release();
		pSampler->Release();

		delete pVertices;
		delete pIndices;
		delete pSpriteCB;
	}
}

void SpriteRenderer::onStart()
{
}

void SpriteRenderer::onUpdate()
{
}

void SpriteRenderer::draw()
{
	if (!isActive()) return;
	if (m_pSRV == nullptr) return;
	if (Camera::isCulling2D(getPosition(), getSize())) return;

	auto pDeviceContext = DirectXManager::getDeviceContext();

	//���_�o�b�t�@���Z�b�g
	auto vertices = pVertices->getBuffer();
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@���Z�b�g
	pDeviceContext->IASetIndexBuffer(pIndices->getBuffer(), DXGI_FORMAT_R32_UINT, 0);
	//�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(pInputLayout);

	//VertexShader���Z�b�g
	pDeviceContext->VSSetShader(m_pVertexShader->getShader(), NULL, 0);
	//PixelShader���Z�b�g
	pDeviceContext->PSSetShader(m_pPixelShader->getShader() , NULL, 0);

	SpriteConstantBuffer constantBuffer;

	//���[���h�s��
	XMMATRIX world = m_pUser->getTransform()->getWorldMatrix();

	//�s�������+�]�u
	XMMATRIX wvp = XMMatrixTranspose(world * Camera::getViewProjMatrix2D());

	//���g�̊e��v���p�e�B���R���X�^���g�o�b�t�@�ɃZ�b�g
	//���[���h�s��
	XMStoreFloat4x4(&constantBuffer.wvpMatrix, wvp);
	//�s�{�b�g
	constantBuffer.pivot = { m_ImagePivot.x, m_ImagePivot.y, 0.0f, 0.0f };
	//�F(���u��)
	XMStoreFloat4(&constantBuffer.color, m_Color.toXMVECTOR());
	//UV�ݒ�̍���
	constantBuffer.uvOffset = { m_UVRect.x, m_UVRect.y };
	//UV�ݒ�̉E��
	constantBuffer.uvSize = { m_UVRect.width, m_UVRect.height };

	//UpdateSubresource�ŃR���X�^���g�o�b�t�@���X�V
	auto cBuffer = pSpriteCB->getBuffer();
	pDeviceContext->UpdateSubresource(cBuffer, 0, NULL, &constantBuffer, NULL, NULL);
	pDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	//�e�N�X�`����ݒ�
	pDeviceContext->PSSetShaderResources(0, 1, &m_pSRV);
	
	//�T���v���[��ݒ�
	pDeviceContext->PSSetSamplers(0, 1, &pSampler);

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->DrawIndexed(6, 0, 0);
}

void SpriteRenderer::setTexture(ID3D11ShaderResourceView * pSRV)
{
	m_pSRV = pSRV;
}

void SpriteRenderer::setTextureByName(const std::string& textureName)
{
	m_pSRV = TextureManager::getTextureView(textureName);
}

void SpriteRenderer::setColor(Color color)
{
	m_Color = color;
}

void SpriteRenderer::setFlipX(bool flipX)
{
	m_FlipX = flipX;
}

void SpriteRenderer::setFlipY(bool flipY)
{
	m_FlipY = flipY;
}

Vec2 SpriteRenderer::getPivot()
{
	return m_ImagePivot;
}

void SpriteRenderer::setPivot(Vec2 pivot)
{
	m_ImagePivot = pivot;
}

RectF SpriteRenderer::getUVRect()
{
	return m_UVRect;
}

void SpriteRenderer::setUVRect(RectF uvRect)
{
	m_UVRect = uvRect;
}