#ifndef SWAY_GL_VERTEXELEMENTSEMANTIC_H
#define SWAY_GL_VERTEXELEMENTSEMANTIC_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum VertexElementSemantic {
	kVertexElementSemantic_Position = 0x0605,
	kVertexElementSemantic_Color    = 0x3407,
	kVertexElementSemantic_TexCoord = 0x309F,
	kVertexElementSemantic_Normal   = 0x8CB7,
	kVertexElementSemantic_Tangent  = 0x549F,
	kVertexElementSemantic_Binormal = 0x5018
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXELEMENTSEMANTIC_H