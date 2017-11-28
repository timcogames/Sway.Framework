#ifndef SWAY_GL_COMPAREFUNC_H
#define SWAY_GL_COMPAREFUNC_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum CompareFunc {
	kCompareFunc_Never        = 0xC7A6,
	kCompareFunc_Always       = 0xA8C7,
	kCompareFunc_Equal        = 0xA1A1,
	kCompareFunc_NotEqual     = 0xE9E3,
	kCompareFunc_Less         = 0xCD24,
	kCompareFunc_LessEqual    = 0x648D,
	kCompareFunc_Greater      = 0x981F,
	kCompareFunc_GreaterEqual = 0x5AE0
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_COMPAREFUNC_H