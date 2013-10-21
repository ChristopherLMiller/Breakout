#include "directx.h"
#include <d3d11.h>
#include <string>

// Function: DirectX()
// Purpose: default constructor
// Inputs: none
// Outputs: none
DirectX::DirectX()
{
	// TODO: implement anything that might need to be
}

// Function: ~DirectX()
// Purpose: destructor
// Inputs: none
// Outputs: none
DirectX::~DirectX()
{
	if (getVersion() == 11) 
	{
		m_d3dDevice->Release();
		m_d3dImmediateContext->Release();
		m_swapChain->Release();
	}
}

// Function initialize(int)
// Purpose: initialize the directx interface
// Inputs: int version - dx version
// Outputs: bool success - if initialization passed
bool DirectX::initialize(int version, HWND hwnd, bool fullscreen = false, UINT sampleCount = 4, int bitsPerPixel = 32, int width = 1024, int height = 768)
{
	// preset samplecount
	if (!setDirectXVersion(version))
		return false;

	if (!setSampleCount(sampleCount))
		return false;

	if (!setBitsPerPixel(bitsPerPixel))
		return false;

	enableFullScreen(fullscreen);

	setResolution(width, height);
	setWindowHandle(hwnd);

	if (version == 9)
	{
		// initialize dx 9
		if (createDirectX9())
		{
			logger.info("Running DirectX version 9");
			return true;
		}
		else 
		{
			logger.error("DirectX 9 creation failed");
			return false;
		}
	}
	else if (version == 10)
	{
		if (createDirectX10())
		{
			logger.info("Running DirectX version 10");
			return true;
		}
		else
		{
			logger.error("DirectX 10 creation failed");
			return false;
		}
	}
	else if (version == 11)
	{
		if (createDirectX11())
		{
			logger.info("Running DirectX Version 11");
			return true;
		} else
		{
			logger.error("DirectX 11 creation failed");
			return false;
		}
	}
	else
	{
		logger.error("Unrecognized DirectX Version in initialize()");
		return false;
	}
}

// Function: setSampleCount(UINT)
// Purpose: set msaa sample count
// Inputs: UINT count - count to set to
// Outputs: bool - if successful
bool DirectX::setSampleCount(UINT count)
{
	if (getVersion() == 9)
	{
		// 9 specific implementation
		return false;
	}
	else if (getVersion() == 10)
	{
		// 10 specific version
		return false;
	}
	else if (getVersion() == 11)
	{
		// 11 specific version
		if (count < 4)
		{
			logger.error("Minimum MSAA sample count allowed with DX 11 is 4, please fix config!");
			return false;
		}
		else if (count > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT)
		{
			logger.error("Maximum MSAA sample count allowed with DX 11 is 32, please fix config!");
			return false;
		}
		else
		{
			m_msaaSampleCount = count;
			return true;
		}
	}
	else
	{
		logger.error("Invalid DX version detected in setSampleCount()");
		return false;
	}
}

// Function: setDirectXVersion(int)
// Purpose: set directx version
// Inputs: int version - version to use
// Outputs: bool - if successful
bool DirectX::setDirectXVersion(int version)
{
	if ((version == 9) || ( version == 10) || (version == 11))
	{
		m_directXVersion = version;
		return true;
	}
	logger.error("Invalid DirectX Version specified: setDirectXVersion()");
	return false;
}

// Function: setBitsPerPixel(int)
// Purpose: set bits per pixel
// Inputs: int bits - bits per pixel to use
// Outpus: bool - if successful
bool DirectX::setBitsPerPixel(int bitsPerPixel)
{
	if (bitsPerPixel == 32)
		m_bitsPerPixel = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (bitsPerPixel == 64)
		m_bitsPerPixel = DXGI_FORMAT_R16G16B16A16_UNORM;
	else
	{
		logger.error("Invalid bits per pixel specificed,  32 or 64 bit only");
		return false;
	}

	return true;
}

// Function: setResolution(int, int)
// Purpose: set width and height
// Inputs; int width - width to set
//         int height - height to set
// Outputs: bool - successfully set
bool DirectX::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;

	return true;
}

// Funcdtion: getVersion()
// Purpose: get directx version
// Inputs: none
// Outputs: int version - version to return
int DirectX::getVersion()
{
	return m_directXVersion;
}

// Function: getSampleCount()
// Purpose: get MSAA sample count
// Inputs: none
// Outputs: int sampleCount
int DirectX::getSampleCount()
{
	return m_msaaSampleCount;
}

// Function: getBitsPerPixel()
// Purpose: get bits per pixel
// Inputs: none
// Outputs: DXGI_FORMAT
DXGI_FORMAT DirectX::getBitsPerPixel()
{
	return m_bitsPerPixel;
}

// Function: getSupportedResolutions()
// Purpose: get array of supported resolutions
// Inputs: none - TODO
// Outputs: none - TODO
void DirectX::getSupportedResolutions()
{
}

// Function: enableFullScreen(bool)
// Purpose: reset device to enable fullscreen and windowed
// Inputs: bool enable - whether to go fullscreen or windowed
// Outputs: bool - whether changed successfully
void DirectX::enableFullScreen(bool enable)
{
	m_fullScreen = enable;
}

// Function: setWindowHandle(HWND)
// Purpose: set window handle
// Inputs: HWND handle - handle to set
// Outputs: bool - successful
bool DirectX::setWindowHandle(HWND hwnd)
{
	m_windowHandle = hwnd;
	return true;
}

// Function: getWindowHandle()
// Purpose: get window handle
// Inputs: none
// Outputs: HWND - instance to window handle
HWND DirectX::getWindowHandle()
{
	return m_windowHandle;
}

// Function: getFullScreen()
// Purpose: whether fullscreen is enabled or not
// Inputs: none
// Outputs: bool - if fullscreen
bool DirectX::getWindowed()
{
	return m_fullScreen;
}

// Function: getImmediateContext()
// Purpose: get the immediate device context
// Inputs: none
// Outputs: ID3D11DeviceContext - the context
ID3D11DeviceContext *DirectX::getImmediateContext()
{
	return m_d3dImmediateContext;
}

// Function: getRenderTargetView
// Purpose: get the render target view
// Inputs: none
// Outputs: ID3D11RenderTargetView
ID3D11RenderTargetView *DirectX::getRenderTargetView()
{
	return m_renderTargetView;
}

// Function: getDepthStencilView
// Purpose: get the depth stencil view object
// Inputs: none
// Outputs: ID3D11DepthStencilView - depth stencil object
ID3D11DepthStencilView *DirectX::getDepthStencilView()
{
	return m_depthStencilView;
}

// Function: getSwapChain()
// Purpose: get the swap chain object
// Inputs: none
// Outputs: IDXGISwapChain - the swap chain object
IDXGISwapChain *DirectX::getSwapChain()
{
	return m_swapChain;
}

// Function: createDirectX11()
// Purpose: create directx 11 device
// Inputs: none
// Outputs: bool - if creation successful
bool DirectX::createDirectX11()
{
		// initialize dx 11
		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL featureLevel;

		HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &m_d3dDevice, &featureLevel, &m_d3dImmediateContext);

		// make sure created passed.
		if (FAILED(hr)) 
		{
			logger.error("D3D11CreateDevice Failed");
			return false;
		}

		// verify create version created
		if (featureLevel !=D3D_FEATURE_LEVEL_11_0) {
			logger.error("DirectX 11 not supported");
			
			return false;
		}

		hr = m_d3dDevice->CheckMultisampleQualityLevels(getBitsPerPixel(), getSampleCount(), &m_msaaQuality);
		
		// verify msaa check passed
		if (FAILED(hr))
		{
			logger.error(std::to_string(getSampleCount()) + " isn't supported.");
			return false;
		}

		// log info about quality level
		logger.info("MSAA sample counts: " + std::to_string(getSampleCount()) + " quality level: " + std::to_string(m_msaaQuality-1));

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
			logger.error("Failed to query interface in Initialize();");
			return false;
		}

		IDXGIAdapter *dxgiAdapter = 0;
		if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter)))
		{
			logger.error("Failed to getAdapter");
			return false;
		}

		IDXGIFactory *dxgiFactory = 0;
		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
		{
			logger.error("Failed to getFactory");
			return false;
		}

		if (FAILED(dxgiFactory->CreateSwapChain(m_d3dDevice, &m_swapChainDesc, &m_swapChain)))
		{
			logger.error("Failed to create Swap Chain");
			return false;
		}

		// release the interfaces
		dxgiAdapter->Release();
		dxgiDevice->Release();
		dxgiFactory->Release();

		if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer))))
		{
			logger.error("Failed to get the back buffer");
			return false;
		}

		if (FAILED(m_d3dDevice->CreateRenderTargetView(m_backBuffer, 0, &m_renderTargetView)))
		{
			logger.error("Failed to create render target view");
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
			logger.error("Failed to create depth stencil buffer");
			return false;
		}
		
		if (FAILED(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView)))
		{
			logger.error("Failed to create depth stencil view");
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
}

// Function: createDirectX10()
// Purpose: create directx 10 device
// Inputs: none
// Outputs: bool - if creation successful
bool DirectX::createDirectX10()
{
	return false;
}

// Function: createDirectX9()
// Purpose: create directx 9 device
// Inputs: none
// Outputs: bool - if creation successful
bool DirectX::createDirectX9()
{
	return false;
}