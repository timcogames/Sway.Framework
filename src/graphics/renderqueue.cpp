#include "renderqueue.h"
#include "rendersubqueue.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
RenderQueue::RenderQueue()
	: _priority(kRenderQueuePriority_Normal) {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
RenderQueue::~RenderQueue() {
	for (u32 i = 0; i < RENDER_SUBQUEUE_GROUP_COUNT; ++i)
		_subqueues[i].clear();
}

/*!
 * \brief
 *   Добавляет подочередь \ref RenderSubqueue в группу.
 *
 * \param[in] subqueue
 *   Указатель на обьект класса подочереди, которой следует добавить в контейнер.
 */
void RenderQueue::addSubqueue(const RenderSubqueueRef_t &subqueue) {
	u32 groupIndex = subqueue->getGroupIdx();
	if (groupIndex > RENDER_SUBQUEUE_GROUP_COUNT)
		std::invalid_argument("groupIndex");

	_subqueues[groupIndex].push_back(subqueue);
}

/*!
 * \brief
 *   Удаляет подочередь \ref RenderSubqueue из группы.
 *
 * \param[in] subqueue
 *   Указатель на обьект класса подочереди, которой следует удалить из контейнера.
 */
void RenderQueue::removeSubqueue(const RenderSubqueueRef_t &subqueue) {
	u32 groupIndex = subqueue->getGroupIdx();
	if (groupIndex > RENDER_SUBQUEUE_GROUP_COUNT)
		std::invalid_argument("groupIndex");

	_subqueues[groupIndex].erase(std::remove(_subqueues[groupIndex].begin(), _subqueues[groupIndex].end(), subqueue), _subqueues[groupIndex].end());
}

/*!
 * \brief
 *   Получает группу подочередей по индексу.
 *
 * \param[in] groupIdx
 *   Индекс группы.
 */
RenderSubqueueRefVector_t &RenderQueue::getSubqueueGroupByIdx(u32 groupIdx) {
	return _subqueues[groupIdx];
}

/*!
 * \brief
 *   Устанавливает значение приоритета.
 */
void RenderQueue::setPriority(u32 priority) {
	_priority = priority;
}

/*!
 * \brief
 *   Получает значение приоритета.
 */
u32 RenderQueue::getPriority() const {
	return _priority;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)