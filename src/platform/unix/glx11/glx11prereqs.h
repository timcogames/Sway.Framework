#ifndef SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H
#define SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H

#include "../../../types.h"
#include "../../../defines.h"
#include "../../../memory/safedeletemacros.h"

#include "../../../math/math.h"

#include "../ois/inputmanager.h"
#include "../ois/keyboard.h"
#include "../ois/mouse.h"

#include <stdexcept> // std::runtime_error
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glx.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowEventGeneric;
struct WindowEventCreate;
struct WindowEventResize;
struct WindowEventRedraw;
struct WindowInitialParams;
struct WindowInternalData;

class Canvas;

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_GLX11PREREQS_H