#ifndef SWAY_GL_TEXTUREFILTER_H
#define SWAY_GL_TEXTUREFILTER_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Перечисление уровней фильтрации.
 */
enum TextureFilter {
	kTextureFilter_Nearest        = 0xB943,
	kTextureFilter_Linear         = 0x7D02,
	kTextureFilter_Trilinear      = 0x4C54,
	kTextureFilter_Anisotropic4x  = 0x5F33,
	kTextureFilter_Anisotropic8x  = 0xFAD8,
	kTextureFilter_Anisotropic16x = 0x96EE
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTUREFILTER_H