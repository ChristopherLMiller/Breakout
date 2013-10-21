#ifndef __WNDPROC_H
#define __WNDPROC_H

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif