#ifndef __APPWINDOW_H
#define __APPWINDOW_H

#include <Windows.h>
#include <string>
#include "Logger.h"

class appWindow
{
public:
	appWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);
	HWND getWindowHandle();
	bool createAppWindow();
	void setAppWindowText(LPCWSTR caption);
private:

	WNDPROC m_appWndProc;
	HWND m_hMainWnd;
	HINSTANCE m_hInstance;
	int m_nCmdShow;
	int m_width, m_height;
	Logger m_logger;
};
#endif