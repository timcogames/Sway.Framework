#ifndef SWAY_GL_VERTEXATTRIBUTE_H
#define SWAY_GL_VERTEXATTRIBUTE_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct VertexAttribute {
	s32 location;
	int componentCount;  /*!< Размер аргумента в шейдере. */
	u32 dataType;        /*!< Тип данных. */
	bool normalized;     /*!< Нормализация входных данных. */
	const void *offset;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXATTRIBUTE_H