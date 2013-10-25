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

// Function: toString(const char*)
// Purpose: convert c-style char array to string
// Inputs: const char* value - char array to convert
// Outputs: std::string - value as string
std::string toString(const char* value) {
	return std::string(value, strlen(value));
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