#ifndef SWAY_GL_VERTEXATTRIBUTE_H
#define SWAY_GL_VERTEXATTRIBUTE_H

#include "datatypeinfo.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct VertexAttribute {
	s32 location;
	DataTypeInfo::Types dataType; /*!< Тип данных. */
	int componentCount;
	const void *pointer;
	bool isNormalized;
	bool isEnabled;
	bool isCustomAttribute;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTE_H