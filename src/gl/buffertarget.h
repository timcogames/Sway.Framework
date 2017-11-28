#ifndef SWAY_GL_BUFFERTARGET_H
#define SWAY_GL_BUFFERTARGET_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum BufferTarget {
	kBufferTarget_Array        = 0x2CA1,
	kBufferTarget_ElementArray = 0xE70D,
	kBufferTarget_Uniform      = 0x6986,
	kBufferTarget_Texture      = 0xC14B
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_BUFFERTARGET_H