#ifndef _COMFUNCTIONS_H
#define _COMFUNCTIONS_H

#include <string>
#include "wtypes.h"

std::string toString(bool value);
std::string toString(const char* value);
void GetDesktopResolution(int &horizontal, int &vertical);

#endif