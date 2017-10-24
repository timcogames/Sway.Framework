#ifndef SWAY_GL_VERTEXDATATYPES_H
#define SWAY_GL_VERTEXDATATYPES_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum VertexDataTypes {
	kVertexDataType_Float2 = 0xC97F,
	kVertexDataType_Float3 = 0x131B,
	kVertexDataType_Float4 = 0x0D65
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXDATATYPES_H