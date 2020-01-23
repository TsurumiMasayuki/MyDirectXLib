#pragma once
#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class DirectXManager
{
public:
	static void initialize(HWND* pHWND);
	static void shutdown();

	static IDXGISwapChain* getSwapChain();
	static ID3D11Device* getDevice();
	static ID3D11DeviceContext* getDeviceContext();
	static ID3D11SamplerState* getSamplerState();

	static void clearScreen(const float clearColor[4]);
	static void presentSwapChain();

private:
	DirectXManager(
		ID3D11Device* pDevice,
		ID3D11DeviceContext* pDeviceContext,
		IDXGISwapChain* pSwapChain,
		ID3D11SamplerState* pSamplerState,
		ID3D11BlendState* pBlendState
	);
	~DirectXManager();

private:
	static DirectXManager* pInstance;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11SamplerState* m_pSamplerState;
	ID3D11BlendState* m_pBlendState;
};

