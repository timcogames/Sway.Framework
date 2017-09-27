#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWSIZES_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWSIZES_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

enum WindowSizes
{
	kWindowSize = 0,
	kWindowSize_Min = 1, /*!< Минимальный размер окна. */
	kWindowSize_Max = 2  /*!< Максимальный размер окна. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWSIZES_H