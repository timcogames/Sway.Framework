#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

#define RENDER_SUBQUEUE_GROUP_COUNT 2

enum RenderSubqueueGroups {
	kRenderSubqueueGroup_Opaque = 0,     /*!< Отрисовывать только непрозрачные части. */
	kRenderSubqueueGroup_Transparent = 1 /*!< Отрисовывать только прозрачные части. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H