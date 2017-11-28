#ifndef SWAY_GL_TEXTURECREATEINFO_H
#define SWAY_GL_TEXTURECREATEINFO_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct TextureCreateInfo {
	u32 target;            /*!< Текстурная цель. */
	u32 mipmapLevel;       /*!< Уровень мипмапа. */
	u32 internalFormat;    /*!< Формат в котором хранится текстура. */
	math::TSize<s32> size; /*!< Размер текстуры. */
	u32 format;            /*!< Формат исходного изображения. */
	u32 dataType;          /*!< Тип данных исходного изображения. */
	lpstr pixels;          /*!< Данные изображения. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTURECREATEINFO_H