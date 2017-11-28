#ifndef SWAY_GL_BUFFERDESCRIPTION_H
#define SWAY_GL_BUFFERDESCRIPTION_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct BufferDescription {
	u32 target;
	u32 usage;
	s32 byteStride;
	s32 capacity;   /*!< Количество элементов в массиве. */
	u32 datatype;   /*!< Тип данных. */
};

struct BufferCreateInfo {
	BufferDescription description;
	const void *data; /*!< Первоначальный данные. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_BUFFERDESCRIPTION_H