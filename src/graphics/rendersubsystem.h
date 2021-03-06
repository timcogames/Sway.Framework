#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_H
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_H

#include "graphicsprereqs.h"
#include "../foundation/object.h"
#include "../foundation/context.h"
#include "../foundation/declareobjectmacros.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubsystem : public foundation::Object {
	DECLARE_OBJECT(RenderSubsystem, foundation::Object)

public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	RenderSubsystem(foundation::Context *context);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~RenderSubsystem();

	/*!
	 * \brief
	 *   Создает новую очередь и добавляет её в контейнер.
	 *
	 * \return
	 *   Умный указатель на объект класса очереди.
	 */
	RenderQueueRef_t createQueue();

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
	RenderQueueRef_t getQueueByIdx(u32 index);

	/*!
	 * \brief
	 *   Получает все очереди.
	 */
	RenderQueueRefVector_t getQueues();

	/*!
	 * \brief
	 *   Сортирует очереди по приоритету.
	 */
	void sortQueues();

	/*!
	 * \brief
	 *   Метод отрисовки.
	 */
	void render();

private:
	void _renderSubqueues(RenderQueueRef_t queue, u32 group);

private:
	RenderQueueRefVector_t _queues; /*!< Контейнер очередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBSYSTEM_H