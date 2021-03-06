#ifndef SWAY_GRAPHICS_RENDERQUEUE_H
#define SWAY_GRAPHICS_RENDERQUEUE_H

#include "graphicsprereqs.h"

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
	~RenderQueue();

	/*!
	 * \brief
	 *   Добавляет подочередь \ref RenderSubqueue в группу.
	 *
	 * \param[in] subqueue
	 *   Указатель на обьект класса подочереди, которой следует добавить в контейнер.
	 * 
	 * \sa
	 *   removeSubqueue(const RenderSubqueueRef_t &)
	 */
	void addSubqueue(const RenderSubqueueRef_t &subqueue);

	/*!
	 * \brief
	 *   Удаляет подочередь \ref RenderSubqueue из группы.
	 *
	 * \param[in] subqueue
	 *   Указатель на обьект класса подочереди, которой следует удалить из контейнера.
	 * 
	 * \sa
	 *   addSubqueue(const RenderSubqueueRef_t &)
	 */
	void removeSubqueue(const RenderSubqueueRef_t &subqueue);

	/*!
	 * \brief
	 *   Получает группу подочередей по индексу.
	 *
	 * \param[in] groupIdx
	 *   Индекс группы.
	 */
	RenderSubqueueRefVector_t &getSubqueueGroupByIdx(u32 groupIdx);

	/*!
	 * \brief
	 *   Устанавливает значение приоритета.
	 * 
	 * \sa
	 *   getPriority() const
	 */
	void setPriority(u32 priority);

	/*!
	 * \brief
	 *   Получает значение приоритета.
	 * 
	 * \sa
	 *   setPriority(u32)
	 */
	u32 getPriority() const;

	struct PriorityInDescendingOrder {
		bool operator()(const RenderQueueRef_t &lhs, const RenderQueueRef_t &rhs) const {
			return lhs->getPriority() > rhs->getPriority();
		}
	};

  private:
	u32 _priority; /*!< Приоритет очереди. */
	RenderSubqueueRefVector_t _subqueues[RENDER_SUBQUEUE_GROUP_COUNT]; /*!< Контейнер подочередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERQUEUE_H