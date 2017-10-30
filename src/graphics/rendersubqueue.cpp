#include "rendersubqueue.h"
#include "rendersubqueuegroups.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
RenderSubqueue::RenderSubqueue()
	: _group(kRenderSubqueueGroup_Opaque) {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
RenderSubqueue::~RenderSubqueue() {
	// Empty
}

/*!
 * \brief
 *   Метод отрисовки.
 */
void RenderSubqueue::render() {
	// Empty
}

/*!
 * \brief
 *   Устанавливает индекс группы.
 */
void RenderSubqueue::setGroupIdx(u32 groupIdx) {
	_group = groupIdx;
}

/*!
 * \brief
 *   Получает индекс группы.
 */
u32 RenderSubqueue::getGroupIdx() const {
	return _group;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)