#include "rendersubsystem.h"
#include "renderqueue.h"
#include "renderqueuepriority.h"
#include "rendersubqueue.h"
#include "rendersubqueuegroup.h"

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
RenderSubsystem::RenderSubsystem(foundation::Context *context) : foundation::Object(context) {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
RenderSubsystem::~RenderSubsystem() {
	_queues.clear();
}

/*!
 * \brief
 *   Создает новую очередь \ref RenderQueue и добавляет её в контейнер.
 *
 * \return
 *   Умный указатель на объект класса очереди.
 */
RenderQueueRef_t RenderSubsystem::createQueue() {
	_queues.push_back(boost::make_shared<RenderQueue>());
	return _queues.back();
}

/*!
 * \brief
 *   Получает очередь по индексу.
 *
 * \param[in] index
 *   Индекс очереди.
 * 
 * \return
 *   Умный указатель на объект класса очереди.
 */
RenderQueueRef_t RenderSubsystem::getQueueByIdx(u32 index) {
	return _queues[index];
}

/*!
 * \brief
 *   Получает все очереди.
 */
RenderQueueRefVector_t RenderSubsystem::getQueues() {
	return _queues;
}

/*!
 * \brief
 *   Сортирует очереди по приоритету.
 */
void RenderSubsystem::sortQueues() {
	if (_queues.size() >= 2)
		std::sort(_queues.begin(), _queues.end(), RenderQueue::PriorityInDescendingOrder());
}

/*!
 * \brief
 *   Метод отрисовки.
 */
void RenderSubsystem::render() {
	for (u32 i = 0; i < _queues.size(); ++i) {
		_renderSubqueues(_queues[i], kRenderSubqueueGroup_Opaque);
		_renderSubqueues(_queues[i], kRenderSubqueueGroup_Transparent);
	}
}

void RenderSubsystem::_renderSubqueues(RenderQueueRef_t queue, u32 group) {
	const RenderSubqueueRefVector_t &subqueues = queue->getSubqueueGroupByIdx(group);

	if (subqueues.size() > 0) {
		BOOST_FOREACH (const RenderSubqueueRef_t &subqueue, subqueues)
			subqueue->render();
	}
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)