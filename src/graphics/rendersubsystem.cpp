#include "rendersubsystem.h"
#include "renderqueue.h"
#include "renderqueuepriorities.h"
#include "rendersubqueue.h"

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
RenderSubsystem::RenderSubsystem()
{
	// Empty
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
RenderSubsystem::~RenderSubsystem()
{
	_queues.clear();
}

/*!
 * \brief Создает новую очередь \ref RenderQueue и добавляет её в контейнер.
 *
 * \return Умный указатель на объект класса очереди.
 */
RenderQueuePtr RenderSubsystem::createQueue()
{
	_queues.push_back(boost::make_shared<RenderQueue>());
	return _queues.back();
}

/*!
 * \brief Получает очередь по индексу.
 *
 * \param index Индекс очереди.
 * \return Умный указатель на объект класса очереди.
 */
RenderQueuePtr RenderSubsystem::getQueueByIdx(u32 index)
{
	return _queues[index];
}

/*!
 * \brief Получает все очереди.
 */
RenderQueueVec RenderSubsystem::getQueues()
{
	return _queues;
}

/*!
 * \brief Сортирует очереди по приоритету.
 */
void RenderSubsystem::sortQueues()
{
	if (_queues.size() >= 2)
		std::sort(_queues.begin(), _queues.end(), RenderQueue::PriorityInDescendingOrder());
}

/*!
 * \brief Метод отрисовки.
 */
void RenderSubsystem::render()
{
	for (u32 i = 0; i < _queues.size(); ++i)
	{
		RenderQueuePtr queue = _queues[i];

		const RenderSubqueueVec &opaqueSubueues = queue->getSubqueueGroupByIdx(kRenderSubqueueGroup_Opaque);
		if (opaqueSubueues.size() > 0)
		{
			BOOST_FOREACH (const RenderSubqueuePtr &subqueue, opaqueSubueues)
				subqueue->render();
		}

		const RenderSubqueueVec &transparentSubqueues = queue->getSubqueueGroupByIdx(kRenderSubqueueGroup_Transparent);
		if (transparentSubqueues.size() > 0)
		{
			BOOST_FOREACH (const RenderSubqueuePtr &subqueue, transparentSubqueues)
				subqueue->render();
		}
	}
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)