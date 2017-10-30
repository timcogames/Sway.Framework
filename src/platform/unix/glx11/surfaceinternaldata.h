#ifndef SWAY_PLATFORM_UNIX_GLX11_SURFACEINTERNALDATA_H
#define SWAY_PLATFORM_UNIX_GLX11_SURFACEINTERNALDATA_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *   Внутренние данные поверхности холста.
 */
struct SurfaceInternalData {
	::Display *xDisplay;
	GLXDrawable glxDrawable;
	GLXFBConfig glxFBConfig;
	GLXContext glxContext;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_SURFACEINTERNALDATA_H