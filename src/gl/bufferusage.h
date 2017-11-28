#ifndef SWAY_GL_BUFFERUSAGE_H
#define SWAY_GL_BUFFERUSAGE_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum BufferUsage {
	kBufferUsage_Static  = 0xA0E7,
	kBufferUsage_Dynamic = 0xF1D8,
	kBufferUsage_Stream  = 0x7F94
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_BUFFERUSAGE_H