#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUP_H
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUP_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

enum RenderSubqueueGroup {
	kRenderSubqueueGroup_Opaque      = 0, /*!< Отрисовывать только непрозрачные части. */
	kRenderSubqueueGroup_Transparent = 1  /*!< Отрисовывать только прозрачные части. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUEGROUP_H