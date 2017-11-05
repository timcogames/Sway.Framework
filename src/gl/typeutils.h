#ifndef SWAY_GL_TYPEUTILS_H
#define SWAY_GL_TYPEUTILS_H

#include "../defines.h"
#include "../types.h"

#include <GL/gl.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class TypeUtils {
public:
	static u32 toGL(u32 type) {
		switch (type) {
		case kType_Int:    return GL_INT;
		case kType_Float:  return GL_FLOAT;
		case kType_Double: return GL_DOUBLE;
		case kType_Short:  return GL_SHORT;
		case kType_Char:   return GL_BYTE;
		/* Поддерживаемые форматы индексов. */
		case kType_UInt:   return GL_UNSIGNED_INT;
		case kType_UShort: return GL_UNSIGNED_SHORT;
		case kType_UChar:  return GL_UNSIGNED_BYTE;
		default:
			return INVALID_TYPE;
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TYPEUTILS_H