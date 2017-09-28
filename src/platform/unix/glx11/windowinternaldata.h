#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowInternalData
{
	::Display *display; /*!< Идентификатор сервера. */
	::Window root;      /*!< Идентификатор корневого окна. */
	::Window window;    /*!< Идентификатор окна. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWINTERNALDATA_H