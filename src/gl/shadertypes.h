#ifndef SWAY_GL_SHADERTYPES_H
#define SWAY_GL_SHADERTYPES_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum ShaderTypes {
	kShaderType_Vertex = 0x8B31,  /*!< Вершинный шейдер. */
	kShaderType_Fragment = 0x8B30 /*!< Фрагментный шейдер. */
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERTYPES_H