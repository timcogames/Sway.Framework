#ifndef SWAY_GL_CULLFACES_H
#define SWAY_GL_CULLFACES_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum CullFaces {
	kCullFace_Back  = 0xCBA3,
	kCullFace_Front = 0x391D
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_CULLFACES_H