#ifndef SWAY_GL_VERTEXATTRIBUTE_H
#define SWAY_GL_VERTEXATTRIBUTE_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct VertexAttribute {
	s32 location;
	u32 dataType; /*!< Тип данных. */
	int componentCount;
	const void *pointer;
	bool enabled;
	bool normalized;
	bool customized;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTE_H