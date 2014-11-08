#pragma once

#include <d3d11.h>
#include "BaseRenderer.h"
#include "Logger.h"

class DX11Renderer : public BaseRenderer {
public:
	DX11Renderer();
	~DX11Renderer();

	bool intialize(HWND hwnd, bool fullscreen = false, UINT sampleCount = 4, int bitsPerPixel = 32, int width = 1024, int height = 768);
	bool setSampleCount(UINT count);
	bool setBitsPerPixel(int bitsPerPixel);
	DXGI_FORMAT getBitsPerPixel();
	bool setResolution(int width, int height);
	int getSampleCount();
	void enableFullScreen(bool enable);
	bool setWindowHandle(HWND hwnd);
	HWND getWindowHandle();
	bool getWindowed();
	bool createDevice();

	void clearBackBuffer(float color[]);
	void clearDepthStencil(float depth = 1.0f);

	void present();

private:
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dImmediateContext;
	IDXGISwapChain *m_swapChain;
	Logger m_logger;

	UINT m_msaaSampleCount;
	UINT m_msaaQuality;
	DXGI_FORMAT m_bitsPerPixel;
	bool m_fullScreen;
	HWND m_windowHandle;
	int m_width, m_height;

	DXGI_SWAP_CHAIN_DESC m_swapChainDesc;

	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11Texture2D *m_backBuffer;
	D3D11_TEXTURE2D_DESC m_depthStencilDesc;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilView *m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
};

