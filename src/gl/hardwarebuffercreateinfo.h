#ifndef SWAY_GL_HARDWAREBUFFERCREATEINFO_H
#define SWAY_GL_HARDWAREBUFFERCREATEINFO_H

#include "hardwarebufferusages.h"
#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct HardwareBufferCreateInfo
{
	HardwareBufferUsages usage;
	s32 byteStride;
	s32 capacity;
	const void* data;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFERCREATEINFO_H