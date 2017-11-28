#ifndef SWAY_GL_PIXELFORMAT_H
#define SWAY_GL_PIXELFORMAT_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum PixelFormat {
	kPixelFormat_R       = 0xEAE9,
	kPixelFormat_R32F    = 0xC561,
	kPixelFormat_RG      = 0x579C,
	kPixelFormat_RGB     = 0x8956,
	kPixelFormat_RGBA    = 0x6445,
	kPixelFormat_RGBA32F = 0x6836, // or HDR
	kPixelFormat_HDR     = 0xEFB1, // or RGBA32F
	kPixelFormat_DEPTH   = 0xB0FC,

	kPixelFormat_BGR     = 0x91D6,
	kPixelFormat_BGRA    = 0x5B8E,
	kPixelFormat_RGB8    = 0x92AE,
	kPixelFormat_RGBA8   = 0x184D
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_PIXELFORMAT_H