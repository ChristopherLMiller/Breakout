#ifndef __BASEDX_H
#define __BASEDX_H

#include <Windows.h>

class BaseDX {
public:
	BaseDX();
	~BaseDX();

	virtual bool intialize(HWND hwnd, bool fullscreen = false, UINT sampleCount = 4, int bitsPerPixel = 32, int width = 1024, int height = 768) = 0;
	virtual bool setSampleCount(UINT count) = 0;
	virtual bool setBitsPerPixel(int bitsPerPixel) = 0;
	virtual bool setResolution(int width, int height) = 0;
	virtual int getVersion() = 0;
	virtual int getSampleCount() = 0;
	virtual void enableFullScreen(bool enable) = 0;
	virtual bool setWindowHandle(HWND hwnd) = 0;
	virtual HWND getWindowHandle() = 0;
	virtual bool getWindowed() = 0;
	virtual bool createDevice() = 0;
};

#endif