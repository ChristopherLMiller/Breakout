#include "appWindow.h"
#include "Logger.h"
#include <Windows.h>
#include <string>
#include "wndproc.h"

// Function: appWindow(HINSTANCE, int, int, int, string)
// Purpose: constructor - all arguments must be supplied
// Inputs: HINSTANCE hInstance - handle to the window instance
//		   int nCmdSHow - show the window
//		   int width - width of the window
//		   int height - height of the window
//		   string windowMode - window mode for the window
// Outputs: none
appWindow::appWindow(HINSTANCE hInstance, int nCmdShow, int width, int height, std::string windowMode = "windowed")
{
	m_hInstance = hInstance;
	m_nCmdShow = nCmdShow;
	m_width = width;
	m_height = height;
	
	// set window style based on the string provided
	if (windowMode == "fullscreen" || windowMode == "borderless") {
		m_windowStyle = WS_POPUP;
	} else {
		m_windowStyle = WS_EX_LAYERED | WS_EX_TOPMOST;
	}

	m_logger = Logger();
	m_appWndProc = WndProc;
}


// Function: getWindowHandle()
// Purpose: get the handle to the window
// Inputs: none
// Outputs: HWND handle - handle to the window
HWND appWindow::getWindowHandle()
{
	return m_hMainWnd;
}

// Function: createAppWindow()
// Purpose: create the window
// Inputs: none
// Outputs: bool success - if creation passed
bool appWindow::createAppWindow()
{
	// the first task is to create wndclass structure to describe the window
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass";

	// next register this class with windows so that we can create a window based on it
	if (!RegisterClass(&wc))
	{
		m_logger.error("RegisterClass Failed!  Terminating");
		return false;
	}

	// with instance registered, we can create the window
	m_hMainWnd = CreateWindowEx(WS_EX_APPWINDOW, L"BasicWndClass", L"Win32Basic", m_windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, 0, 0, m_hInstance, 0);

	if (m_hMainWnd == 0) 
	{
		m_logger.error("Creation of window failed! Terminating");
		return false;
	}

	// show and start updating the window
	ShowWindow(m_hMainWnd, m_nCmdShow);
	UpdateWindow(m_hMainWnd);

	return true;
}

// Function: setAppWindowText(std::string)
// Purpose: set app window text
// Inputs: std::string caption
// Outputs: none
void appWindow::setAppWindowText(LPCWSTR caption)
{
	SetWindowText(getWindowHandle(), caption);
}