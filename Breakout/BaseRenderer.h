#pragma once

#include <Windows.h>

class BaseRenderer {
public:
	virtual bool intialize(HWND hwnd, bool fullscreen = false, UINT sampleCount = 4, int bitsPerPixel = 32, int width = 1024, int height = 768) = 0;
	virtual bool setSampleCount(UINT count) = 0;
	virtual bool setBitsPerPixel(int bitsPerPixel) = 0;
	virtual bool setResolution(int width, int height) = 0;
	virtual int getSampleCount() = 0;
	virtual void enableFullScreen(bool enable) = 0;
	virtual bool setWindowHandle(HWND hwnd) = 0;
	virtual HWND getWindowHandle() = 0;
	virtual bool getWindowed() = 0;
	virtual bool createDevice() = 0;

	virtual void clearBackBuffer(float color[]) = 0;
	virtual void clearDepthStencil(float depth = 1.0f) = 0;
	virtual void present()= 0;
};