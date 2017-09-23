#include "rendersubqueue.h"
#include "rendersubqueuegroups.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
RenderSubqueue::RenderSubqueue()
	: _group(kRenderSubqueueGroup_Opaque)
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
RenderSubqueue::~RenderSubqueue()
{
	// Empty
}

/*!
 * \brief Метод отрисовки.
 */
void RenderSubqueue::render()
{
	// Empty
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)