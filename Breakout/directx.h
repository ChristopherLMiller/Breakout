#ifndef __DIRECTX_H
#define __DIRECTX_H

#include <d3d11.h>
#include "Logger.h"
#include "Config.h"

class DirectX 
{
public:
	DirectX();
	~DirectX();

	bool initialize(int dxVersion, HWND hwnd, bool fullScreen, UINT sampleCount, int bitsPerPixel, int width, int height);

	void getSupportedResolutions();	// need to define parameters based on datatype of resolutions
	void enableFullScreen(bool enable);

	bool setSampleCount(UINT count);
	bool setDirectXVersion(int version);
	bool setBitsPerPixel(int bitsPerPixel);
	bool setResolution(int width, int height);
	bool setWindowHandle(HWND hwnd);

	int getVersion();
	int getSampleCount();
	DXGI_FORMAT getBitsPerPixel();
	HWND getWindowHandle();
	bool getWindowed();
	ID3D11DeviceContext *getImmediateContext();
	ID3D11RenderTargetView *getRenderTargetView();
	ID3D11DepthStencilView *getDepthStencilView();
	IDXGISwapChain *getSwapChain();

protected:
	bool createDirectX11();
	bool createDirectX10();
	bool createDirectX9();

private:
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dImmediateContext;
	bool m_fullScreen;
	Logger logger;
	UINT m_msaaQuality;
	UINT m_msaaSampleCount;
	int m_directXVersion;
	DXGI_FORMAT m_bitsPerPixel;
	DXGI_SWAP_CHAIN_DESC m_swapChainDesc;
	int m_width;
	int m_height;
	HWND m_windowHandle;
	IDXGISwapChain *m_swapChain;
	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11Texture2D *m_backBuffer;
	D3D11_TEXTURE2D_DESC m_depthStencilDesc;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilView *m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
};
#endif
