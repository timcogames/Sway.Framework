#ifndef SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H
#define SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H

#include "../../../types.h"
#include "../../../defines.h"
#include "../../../memory/safedeletemacros.h"

#include "../../../math/size.h"
#include "../../../math/sizehints.h"

#include <stdexcept> // std::runtime_error
#include <X11/Xlib.h>
#include <X11/Xutil.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowConfig;

class Canvas;

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H