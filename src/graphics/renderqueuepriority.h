#ifndef SWAY_GRAPHICS_RENDERQUEUEPRIORITY_H
#define SWAY_GRAPHICS_RENDERQUEUEPRIORITY_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * Типы приоритетов.
 */
enum RenderQueuePriority {
	kRenderQueuePriority_VeryLow  = 0, /*!< Очень низкий приоритет. */
	kRenderQueuePriority_Low      = 1, /*!< Низкий приоритет. */
	kRenderQueuePriority_Normal   = 2, /*!< Средний приоритет. */
	kRenderQueuePriority_High     = 3, /*!< Высокий приоритет. */
	kRenderQueuePriority_VeryHigh = 4  /*!< Очень высокий приоритет. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERQUEUEPRIORITY_H