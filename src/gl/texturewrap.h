#ifndef SWAY_GL_TEXTUREWRAP_H
#define SWAY_GL_TEXTUREWRAP_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum TextureWrap {
	kTextureWrap_Repeat = 0x6EC0,
	kTextureWrap_Clamp  = 0xC50F
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTUREWRAP_H