#ifndef SWAY_GL_HARDWAREBUFFERUSAGES_H
#define SWAY_GL_HARDWAREBUFFERUSAGES_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum HardwareBufferUsages {
	kHardwareBufferUsage_Static  = 0xA0E7,
	kHardwareBufferUsage_Dynamic = 0xF1D8,
	kHardwareBufferUsage_Stream  = 0x7F94
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFERUSAGES_H