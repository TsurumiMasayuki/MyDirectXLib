#pragma once
#include "Utility\Color.h"

struct ID3D11Device;
struct ID3D11DeviceContext;

struct ID3D11Resource;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct ID3D11DepthStencilView;

//レンダーターゲット用クラス
class RenderTarget
{
public:
	RenderTarget(float width, float height);
	RenderTarget(ID3D11Texture2D* pRenderTexture);
	~RenderTarget();

	void setClearColor(const Color& color) { m_ClearColor = color; }

	void setRenderTarget(bool useDepthBuffer);
	void clearRenderTarget();

	ID3D11Texture2D* getRenderTexture() { return m_pRenderTexture; }
	ID3D11ShaderResourceView* getSRV();

private:
	ID3D11Texture2D* m_pRenderTexture;
	ID3D11RenderTargetView* m_pRTV;

	ID3D11Texture2D* m_pDepthTexture;
	ID3D11DepthStencilView* m_pDSV;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	Color m_ClearColor;
};