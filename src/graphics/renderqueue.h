#ifndef SWAY_GRAPHICS_RENDERQUEUE_H
#define SWAY_GRAPHICS_RENDERQUEUE_H

#include "prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderQueue {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	RenderQueue();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~RenderQueue();

	/*!
	 * \brief
	 *   Добавляет подочередь \ref RenderSubqueue в группу.
	 *
	 * \param[in] subqueue
	 *   Указатель на обьект класса подочереди, которой следует добавить в контейнер.
	 */
	virtual void addSubqueue(const RenderSubqueuePtr &subqueue);

	/*!
	 * \brief
	 *   Удаляет подочередь \ref RenderSubqueue из группы.
	 *
	 * \param[in] subqueue
	 *   Указатель на обьект класса подочереди, которой следует удалить из контейнера.
	 */
	virtual void removeSubqueue(const RenderSubqueuePtr &subqueue);

	/*!
	 * \brief
	 *   Получает группу подочередей по индексу.
	 *
	 * \param[in] groupIdx
	 *   Индекс группы.
	 */
	virtual RenderSubqueueVec &getSubqueueGroupByIdx(u32 groupIdx);

	/*!
	 * \brief
	 *   Устанавливает значение приоритета.
	 */
	virtual void setPriority(u32 priority);

	/*!
	 * \brief
	 *   Получает значение приоритета.
	 */
	virtual u32 getPriority() const;

	struct PriorityInDescendingOrder {
		bool operator()(const RenderQueuePtr &lhs, const RenderQueuePtr &rhs) const {
			return lhs->getPriority() > rhs->getPriority();
		}
	};

  private:
	u32 _priority; /*!< Приоритет очереди. */
	RenderSubqueueVec _subqueues[RENDER_SUBQUEUE_GROUP_COUNT]; /*!< Контейнер подочередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERQUEUE_H