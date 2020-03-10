#include "RenderTarget.h"
#include <d3d11.h>
#include "Device\DirectXManager.h"

RenderTarget::RenderTarget(float width, float height)
{
	m_pDevice = DirectXManager::getDevice();
	m_pDeviceContext = DirectXManager::getDeviceContext();

	//レンダーターゲット用テクスチャの作成
	D3D11_TEXTURE2D_DESC renderTexDesc;
	ZeroMemory(&renderTexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	renderTexDesc.Usage = D3D11_USAGE_DEFAULT;
	renderTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	renderTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	renderTexDesc.Width = width;
	renderTexDesc.Height = height;
	renderTexDesc.CPUAccessFlags = 0;
	renderTexDesc.MipLevels = 1;
	renderTexDesc.ArraySize = 1;
	renderTexDesc.SampleDesc.Count = 1;
	renderTexDesc.SampleDesc.Quality = 0;

	m_pDevice->CreateTexture2D(&renderTexDesc, nullptr, &m_pRenderTexture);

	//レンダーターゲットの作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	m_pDevice->CreateRenderTargetView(m_pRenderTexture, &rtvDesc, &m_pRTV);

	//深度バッファ用のテクスチャの作成
	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	
	m_pDevice->CreateTexture2D(&depthTexDesc, nullptr, &m_pDepthTexture);

	//深度バッファの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsDesc.Format = depthTexDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	m_pDevice->CreateDepthStencilView(m_pDepthTexture, &dsDesc, &m_pDSV);
}

RenderTarget::RenderTarget(ID3D11Texture2D * pRenderTexture)
{
	m_pDevice = DirectXManager::getDevice();
	m_pDeviceContext = DirectXManager::getDeviceContext();

	m_pRenderTexture = pRenderTexture;

	//レンダーターゲット用テクスチャの情報
	D3D11_TEXTURE2D_DESC renderTexDesc;
	pRenderTexture->GetDesc(&renderTexDesc);

	//レンダーターゲットの作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	m_pDevice->CreateRenderTargetView(m_pRenderTexture, &rtvDesc, &m_pRTV);

	//深度バッファ用のテクスチャの作成
	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthTexDesc.Width = renderTexDesc.Width;
	depthTexDesc.Height = renderTexDesc.Height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;

	m_pDevice->CreateTexture2D(&depthTexDesc, nullptr, &m_pDepthTexture);

	//深度バッファの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsDesc.Format = depthTexDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	m_pDevice->CreateDepthStencilView(m_pDepthTexture, &dsDesc, &m_pDSV);
}

RenderTarget::~RenderTarget()
{
	m_pRenderTexture->Release();
	m_pRTV->Release();

	m_pDepthTexture->Release();
	m_pDSV->Release();
}

void RenderTarget::setRenderTarget(bool useDepthBuffer)
{
	if (useDepthBuffer)
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	else
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, nullptr);
}

void RenderTarget::clearRenderTarget()
{
	float clearColor[4] = { m_ClearColor.r,m_ClearColor.g, m_ClearColor.b, m_ClearColor.a };

	//レンダーターゲットをクリア
	m_pDeviceContext->ClearRenderTargetView(m_pRTV, clearColor);
	//深度バッファをクリア
	m_pDeviceContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11ShaderResourceView * RenderTarget::getSRV()
{
	ID3D11ShaderResourceView* pSRV;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	m_pDevice->CreateShaderResourceView(m_pRenderTexture, &srvDesc, &pSRV);

	return pSRV;
}
