#include "DX11Renderer.h"


// Funcdtion: DX11Renderer()
// Purpose: Default constructor
// Inputs: none
// Outputs: none
DX11Renderer::DX11Renderer() {

}

// Function ~DX11Renderer()
// Purpose: Default desctructor - clean up resources
// Inputs: none
// Outputs: none
DX11Renderer::~DX11Renderer() {
	m_d3dDevice->Release();
	m_d3dImmediateContext->Release();
	m_swapChain->Release();
}

// Function: initialize(HWND, bool, UINT int, int, int)
// Purpose: Initialize DX11 object
// Inputs: HWND hwnd - handle the the window
//         bool fullscreen - whether app should be fullscreen or not
//         UINT sampleCount - MSAA sample count
//         int bitsPerPixel - how many bits per pixel
//         int width - backbuffer width
//         int height - backbuffer height
bool DX11Renderer::intialize(HWND hwnd, bool fullscreen, UINT sampleCount, int bitsPerPixel, int width, int height) {
	
	// set the MSAA sample count
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
		m_logger.error("DirectX 11 device creation failed");
		return false;
	}


	m_logger.info("Program execution running with DirectX 11");
	return true;
}

// Function: setSampleCount(UINT)
// Purpose: set MSAA sample count
// Inputs: UINT count - count to set
// Outputs: bool - if successful
bool DX11Renderer::setSampleCount(UINT count) {
	if (count < 4) {
		m_logger.error("Minimum MSAA sample count allowed with DirectX11 is 4, please fix config!");
		return false;
	}
	else if (count > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT) {
		m_logger.error("Maximum MSAA sample count allowed with DX11 is 32, please fix config!");
		return false;
	}
	else {
		m_msaaSampleCount = count;
		return true;
	}
}

// Function: setBitsPerPixel(int)
// Purpose: set bits per pixel
// Inputs: int bits - bits per pixel to use
// Outpus: bool - if successful
bool DX11Renderer::setBitsPerPixel(int bitsPerPixel)
{
	if (bitsPerPixel == 32)
		m_bitsPerPixel = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (bitsPerPixel == 64)
		m_bitsPerPixel = DXGI_FORMAT_R16G16B16A16_UNORM;
	else
	{
		m_logger.error("Invalid bits per pixel specificed,  32 or 64 bit only");
		return false;
	}

	return true;
}

// Function: enableFullScreen(bool)
// Purpose: reset device to enable fullscreen and windowed
// Inputs: bool enable - whether to go fullscreen or windowed
// Outputs: bool - whether changed successfully
void DX11Renderer::enableFullScreen(bool enable)
{
	m_fullScreen = enable;
}

// Function: setWindowHandle(HWND)
// Purpose: set window handle
// Inputs: HWND handle - handle to set
// Outputs: bool - successful
bool DX11Renderer::setWindowHandle(HWND hwnd)
{
	m_windowHandle = hwnd;
	return true;
}

// Function: setResolution(int, int)
// Purpose: set width and height
// Inputs; int width - width to set
//         int height - height to set
// Outputs: bool - successfully set
bool DX11Renderer::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;

	return true;
}

// Function: getBitsPerPixel()
// Purpose: get bits per pixel
// Inputs: none
// Outputs: DXGI_FORMAT
DXGI_FORMAT DX11Renderer::getBitsPerPixel()
{
	return m_bitsPerPixel;
}

// Function: getSampleCount()
// Purpose: get MSAA sample count
// Inputs: none
// Outputs: int sampleCount
int DX11Renderer::getSampleCount()
{
	return m_msaaSampleCount;
}

// Function: getFullScreen()
// Purpose: whether fullscreen is enabled or not
// Inputs: none
// Outputs: bool - if fullscreen
bool DX11Renderer::getWindowed()
{
	return m_fullScreen;
}

// Function: getWindowHandle()
// Purpose: get window handle
// Inputs: none
// Outputs: HWND - instance to window handle
HWND DX11Renderer::getWindowHandle()
{
	return m_windowHandle;
}

// Function: createDevice() {
// Purpose: create the directx device
// Inputs: none
// Outputs: bool - if creation was successful
bool DX11Renderer::createDevice() {
	
	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &m_d3dDevice, &featureLevel, &m_d3dImmediateContext);

	if (FAILED(hr)) {
		m_logger.error("D3D11CreateDevice Failed");
		m_logger.error(hr);
		return false;
	}

	// verify create version created
	if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
		m_logger.error("DirectX 11 not supported");
		return false;
	}

	hr = m_d3dDevice->CheckMultisampleQualityLevels(getBitsPerPixel(), getSampleCount(), &m_msaaQuality);

	// verify msaa check passed
	if (FAILED(hr)) {
		m_logger.error(std::to_string(getSampleCount()) + " isn't supported by your GPU");
		return false;
	}

	// log info about quality level
	m_logger.info("MSAA Sample counts: " + std::to_string(getSampleCount()) + " quality level: " + std::to_string(m_msaaQuality - 1));

	// create the swap chain at this point
	m_swapChainDesc.BufferDesc.Width = m_width;
	m_swapChainDesc.BufferDesc.Height = m_height;
	m_swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;	// TODO: enumerate proper refresh rate based on monitor
	m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_swapChainDesc.BufferDesc.Format = getBitsPerPixel();
	m_swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	m_swapChainDesc.SampleDesc.Count = getSampleCount();
	m_swapChainDesc.SampleDesc.Quality = m_msaaQuality - 1;
	m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_swapChainDesc.BufferCount = 1;
	m_swapChainDesc.OutputWindow = m_windowHandle;
	m_swapChainDesc.Windowed = getWindowed();
	m_swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	m_swapChainDesc.Flags = 0;

	IDXGIDevice *dxgiDevice = 0;
	if (FAILED(m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)))
	{
		m_logger.error("Failed to query interface in Initialize();");
		return false;
	}

	IDXGIAdapter *dxgiAdapter = 0;
	if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter)))
	{
		m_logger.error("Failed to getAdapter");
		return false;
	}

	IDXGIFactory *dxgiFactory = 0;
	if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
	{
		m_logger.error("Failed to getFactory");
		return false;
	}

	if (FAILED(dxgiFactory->CreateSwapChain(m_d3dDevice, &m_swapChainDesc, &m_swapChain)))
	{
		m_logger.error("Failed to create Swap Chain");
		return false;
	}

	// release the interfaces
	dxgiAdapter->Release();
	dxgiDevice->Release();
	dxgiFactory->Release();

	if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer))))
	{
		m_logger.error("Failed to get the back buffer");
		return false;
	}

	if (FAILED(m_d3dDevice->CreateRenderTargetView(m_backBuffer, 0, &m_renderTargetView)))
	{
		m_logger.error("Failed to create render target view");
		return false;
	}

	// creat the depth stencil
	m_depthStencilDesc.Width = m_width;
	m_depthStencilDesc.Height = m_height;
	m_depthStencilDesc.MipLevels = 1;
	m_depthStencilDesc.ArraySize = 1;
	m_depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	m_depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_depthStencilDesc.CPUAccessFlags = 0;
	m_depthStencilDesc.MiscFlags = 0;
	m_depthStencilDesc.SampleDesc.Count = getSampleCount();
	m_depthStencilDesc.SampleDesc.Quality = m_msaaQuality - 1;

	if (FAILED(m_d3dDevice->CreateTexture2D(&m_depthStencilDesc, 0, &m_depthStencilBuffer)))
	{
		m_logger.error("Failed to create depth stencil buffer");
		return false;
	}

	if (FAILED(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView)))
	{
		m_logger.error("Failed to create depth stencil view");
		return false;
	}

	m_d3dImmediateContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.Width = static_cast<float>(m_width);
	m_viewport.Height = static_cast<float>(m_height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	m_d3dImmediateContext->RSSetViewports(1, &m_viewport);

	return true;
}

// Function: clearBackBuffer
// Purpose: clear the back buffer to specified color
// Inputs: float color[] - array for the color
// Outputs: none
void DX11Renderer::clearBackBuffer(float color[]) {
	m_d3dImmediateContext->ClearRenderTargetView(m_renderTargetView, color);
}

// Function: clearDepthStencil
// Purpose: clear the depth stencil
// Inputs: float depth - depth to set
// Outputs: none
void DX11Renderer::clearDepthStencil(float depth) {
	m_d3dImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, 0);
}

// Function: present
// Purpose: present the swap chain
// Inputs: none
// Outputs: none
void DX11Renderer::present() {
	m_swapChain->Present(0, 0);
}