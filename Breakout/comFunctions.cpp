#include "comFunctions.h"
#include <string>

// Function toString(bool)
// Purpose: convert boolean to string for display purposes
// Inputs: bool  value - value to convert
// Outputs: std::string - value as string
std::string toString(bool value)
{
	if (value == true)
		return "true";
	else
		return "false";
}

// Function: GetDesktopResolution(int &, int &)
// Purpose: get the desktop resolution
// Inputs: int horizontal - horizontal resolution
//         int vertical - vertical resolution
// Outputs: none
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}