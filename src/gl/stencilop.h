#ifndef SWAY_GL_STENCILOP_H
#define SWAY_GL_STENCILOP_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum StencilOp {
	kStencilOp_Keep,
	kStencilOp_Replace,
	kStencilOp_Increment,
	kStencilOp_IncrementWrap,
	kStencilOp_Decrement,
	kStencilOp_DecrementWrap,
	kStencilOp_Invert
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_STENCILOP_H