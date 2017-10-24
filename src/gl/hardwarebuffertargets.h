#ifndef SWAY_GL_HARDWAREBUFFERTARGETS_H
#define SWAY_GL_HARDWAREBUFFERTARGETS_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum HardwareBufferTargets {
	kHardwareBufferTarget_Array        = 0x2CA1,
	kHardwareBufferTarget_ElementArray = 0xE70D,
	kHardwareBufferTarget_Uniform      = 0x6986,
	kHardwareBufferTarget_Texture      = 0xC14B
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFERTARGETS_H