#ifndef SWAY_GRAPHICS_DRAWABLEDESCRIPTION_H
#define SWAY_GRAPHICS_DRAWABLEDESCRIPTION_H

#include "graphicsprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct DrawableCreateInfo {
	gl::BufferCreateInfo vboInfo;
	gl::BufferCreateInfo iboInfo;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_DRAWABLEDESCRIPTION_H