#ifndef SWAY_PLATFORM_UNIX_OIS_KEYMAPPING_H
#define SWAY_PLATFORM_UNIX_OIS_KEYMAPPING_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

struct KeyMapping {
	KeySym keysym;
	u32 keycode;
};

// struct KeyMapping {
// 	lpcstr charcode;
// 	u32 keycode;
// };

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_KEYMAPPING_H