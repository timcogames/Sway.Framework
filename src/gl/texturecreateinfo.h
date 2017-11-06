#ifndef SWAY_GL_TEXTURECREATEINFO_H
#define SWAY_GL_TEXTURECREATEINFO_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct TextureCreateInfo {
	u32 target;
	u32 width, height;
	u32 arraySize;
	u32 format, internalFormat;
	u32 dataType;
	lpstr pixels;
	u32 mipLevels;
	u32 sampleCount;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTURECREATEINFO_H