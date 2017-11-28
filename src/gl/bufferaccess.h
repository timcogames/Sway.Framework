#ifndef SWAY_GL_BUFFERACCESS_H
#define SWAY_GL_BUFFERACCESS_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum BufferAccess {
	kBufferAccess_Read,
	kBufferAccess_Write,
	kBufferAccess_ReadWrite
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_BUFFERACCESS_H