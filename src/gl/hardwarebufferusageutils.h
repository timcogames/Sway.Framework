#ifndef SWAY_GL_HARDWAREBUFFERUSAGEUTILS_H
#define SWAY_GL_HARDWAREBUFFERUSAGEUTILS_H

#include "hardwarebufferusages.h"
#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class HardwareBufferUsageUtils
{
public:
	static GLenum toGL(HardwareBufferUsages usage)
	{
		switch (usage)
		{
		case kHardwareBufferUsage_Static:  return GL_STATIC_DRAW_ARB;
		case kHardwareBufferUsage_Dynamic: return GL_DYNAMIC_DRAW_ARB;
		case kHardwareBufferUsage_Stream:  return GL_STREAM_DRAW_ARB;
		default:
			return 0;
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFERUSAGEUTILS_H