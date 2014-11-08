#include "DX9Renderer.h"


// Function DX9Renderer()
// Purpose: Default contstructor
// Inputs: none
// Outputs: none
DX9Renderer::DX9Renderer() {

}

// Function: ~DX9Renderer()
// Purpose: clean up any resources
// Inputs: none
// Outputs: none
DX9Renderer::~DX9Renderer() {

}

// Function: initalize(HWND, bool, UINT, int, int, int)
// Purpose: Initialize DX9 object
// Inputs: HWND hwnd - handle to the window
//         bool fullscreen - whether app should be fullscreen or not
//         UINT sampleCount = MSAA sample count
//         int bitsPerPixel - how many bits per pixel
//         int width - backbuffer width
//         int height - backbuffer height;
bool DX9Renderer::intialize(HWND hwnd, bool fullscreen, UINT sampleCount, int bitsPerPixel, int width, int height) {
	
	// Set the MSAA sample count
	if (!setSampleCount(sampleCount)) {
		return false;
	}

	// set the bits per pixel
	if (!setBitsPerPixel(bitsPerPixel)) {
		return false;
	}

	// enable fullscreen if we need to
	enableFullScreen(!fullscreen);

	// set the resolution
	setResolution(width, height);

	// set the window handle
	setWindowHandle(hwnd);

	// create the device
	if (!createDevice()) {
		m_logger.error("Directx 9 device creation failed");
		return false;
	}

	m_logger.info("Program execution running with Directx 9");
	return true;
}

// Function: setSampleCount(UINT)
// Purpose: set MSAA sample count
// Inputs: UINT count - count to set
// Outputs: bool - if successful
bool DX9Renderer::setSampleCount(UINT count) {
	//TODO
	return true;
}


// Function: setBitsPerPixel(int)
// Purpose: set bits per pixel
// Inputs: int bits - bits per pixel to use
// Outpus: bool - if successful
bool DX9Renderer::setBitsPerPixel(int bitsPerPixel)
{
	// TODO

	return true;
}

// Function: enableFullScreen(bool)
// Purpose: reset device to enable fullscreen and windowed
// Inputs: bool enable - whether to go fullscreen or windowed
// Outputs: bool - whether changed successfully
void DX9Renderer::enableFullScreen(bool enable)
{
	m_fullScreen = enable;
}

// Function: setWindowHandle(HWND)
// Purpose: set window handle
// Inputs: HWND handle - handle to set
// Outputs: bool - successful
bool DX9Renderer::setWindowHandle(HWND hwnd)
{
	m_windowHandle = hwnd;
	return true;
}

// Function: setResolution(int, int)
// Purpose: set width and height
// Inputs; int width - width to set
//         int height - height to set
// Outputs: bool - successfully set
bool DX9Renderer::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;

	return true;
}

// Function: getBitsPerPixel()
// Purpose: get bits per pixel
// Inputs: none
// Outputs: DXGI_FORMAT
/*DXGI_FORMAT DX9Renderer::getBitsPerPixel()
{
	return m_bitsPerPixel;
}*/

// Function: getSampleCount()
// Purpose: get MSAA sample count
// Inputs: none
// Outputs: int sampleCount
int DX9Renderer::getSampleCount()
{
	return m_msaaSampleCount;
}

// Function: getFullScreen()
// Purpose: whether fullscreen is enabled or not
// Inputs: none
// Outputs: bool - if fullscreen
bool DX9Renderer::getWindowed()
{
	return m_fullScreen;
}

// Function: getWindowHandle()
// Purpose: get window handle
// Inputs: none
// Outputs: HWND - instance to window handle
HWND DX9Renderer::getWindowHandle()
{
	return m_windowHandle;
}

// Function: createDevice()
// Purpose: create the directx device
// Inputs: none
// Outputs: bool - if creation successful
bool DX9Renderer::createDevice() {
	// TODO

	return true;
}

// Function: clearBackBuffer
// Purpose: clear the back buffer to the specified color
// Inputs: float color[] - array for the color
// Outputs: none
void DX9Renderer::clearBackBuffer(float color[]) {
	// TODO
}

// Function: clearDepthStencil
// Purpose: clear the depth buffer
// Inputs: float depth - depth to set
// Outputs: none
void DX9Renderer::clearDepthStencil(float depth) {
	// TODO
}

// Function: present
// Purpose: present the swap chain
// Inputs: none
// Outputs: none
void DX9Renderer::present() {
	// TODO
}



