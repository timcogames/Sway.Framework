#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_H
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_H

#include "prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubsystem
{
 public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	RenderSubsystem();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	virtual ~RenderSubsystem();

	/*!
	 * \brief Создает новую очередь и добавляет её в контейнер.
	 *
	 * \return Умный указатель на объект класса очереди.
	 */
	virtual RenderQueuePtr createQueue();

	/*!
	 * \brief Получает очередь по индексу.
	 *
	 * \param index Индекс очереди.
	 * \return Умный указатель на объект класса очереди.
	 */
	virtual RenderQueuePtr getQueueByIdx(u32 index);

	/*!
	 * \brief Получает все очереди.
	 */
	virtual RenderQueueVec getQueues();

	/*!
	 * \brief Сортирует очереди по приоритету.
	 */
	virtual void sortQueues();

	/*!
	 * \brief Метод отрисовки.
	 */
	virtual void render();

 private:
	RenderQueueVec _queues; /*!< Контейнер очередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBSYSTEM_H