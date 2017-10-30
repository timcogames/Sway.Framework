#ifndef SWAY_PLATFORM_UNIX_GLX11_WINDOWEVENTS_H
#define SWAY_PLATFORM_UNIX_GLX11_WINDOWEVENTS_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowEventGeneric {
	// Empty
};

struct WindowEventCreate {
	math::TPoint<s32> position;
	math::TSize<s32> size;
};

struct WindowEventResize {
	math::TSize<s32> size;
};

struct WindowEventRedraw {
	math::TPoint<s32> position;
	math::TSize<s32> size;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_WINDOWEVENTS_H