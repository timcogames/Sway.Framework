#ifndef SWAY_GL_TEXTURETARGET_H
#define SWAY_GL_TEXTURETARGET_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum TextureTarget {
	kTextureTarget_2D                   = 0xF2DF, /*!< Двухмерная текстура. */
	kTextureTarget_2D_Array             = 0x347E,
	kTextureTarget_2D_MultiSample       = 0x14F1,
	kTextureTarget_2D_MultiSample_Array = 0xF596,
	kTextureTarget_Rectangle            = 0xA15A,
	kTextureTarget_CubeMap              = 0x4E2D  /*!< Кубическая текстура. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTURETARGET_H