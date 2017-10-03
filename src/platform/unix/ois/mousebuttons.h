#ifndef SWAY_PLATFORM_UNIX_OIS_MOUSEBUTTONT_H
#define SWAY_PLATFORM_UNIX_OIS_MOUSEBUTTONT_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

enum MouseButtons
{
	kMouseButton_Left   = 0,
	kMouseButton_Middle = 1,
	kMouseButton_Right  = 2
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_MOUSEBUTTONT_H