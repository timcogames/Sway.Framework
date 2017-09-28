#ifndef SWAY_PLATFORM_UNIX_OIS_KEYBOARDEVENTS_H
#define SWAY_PLATFORM_UNIX_OIS_KEYBOARDEVENTS_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

struct InputEventKeyPress
{
	u32 keycode;
};

struct InputEventKeyRelease
{
	u32 keycode;
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_KEYBOARDEVENTS_H