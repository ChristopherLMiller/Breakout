#pragma once

#include <d3d9.h>
#include "Logger.h"
#include "BaseRenderer.h"

class DX9Renderer :	public BaseRenderer
{
public:
	DX9Renderer();
	~DX9Renderer();

	bool intialize(HWND hwnd, bool fullscreen = false, UINT sampleCount = 4, int bitsPerPixel = 32, int width = 1024, int height = 768);
	bool setSampleCount(UINT count);
	bool setBitsPerPixel(int bitsPerPixel);
	
	// DXGI_FORMAT getBitsPerPixel();

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
	Logger m_logger;

	bool m_fullScreen;
	HWND m_windowHandle;
	int m_width, m_height;
	int m_msaaSampleCount;
};

