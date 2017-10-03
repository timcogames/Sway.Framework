#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWMODES_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWMODES_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

enum WindowModes
{
	kWindowMode_Windowed = 0,  /*!< Оконный режим. */
	kWindowMode_Fullscreen = 1 /*!< Полноэкранный режим. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWMODES_H