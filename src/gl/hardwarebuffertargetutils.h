#ifndef SWAY_GL_HARDWAREBUFFERTARGETUTILS_H
#define SWAY_GL_HARDWAREBUFFERTARGETUTILS_H

#include "hardwarebuffertargets.h"
#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class HardwareBufferTargetUtils
{
public:
	static GLenum toGL(HardwareBufferTargets target)
	{
		switch (target)
		{
		case kHardwareBufferTarget_Array:        return GL_ARRAY_BUFFER_ARB;
		case kHardwareBufferTarget_ElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
		case kHardwareBufferTarget_Uniform:      return GL_UNIFORM_BUFFER;
		case kHardwareBufferTarget_Texture:      return GL_TEXTURE_BUFFER_ARB;
		default:
			return 0;
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_HARDWAREBUFFERTARGETUTILS_H