#ifndef SWAY_GRAPHICS_RENDERSUBQUEUE_H
#define SWAY_GRAPHICS_RENDERSUBQUEUE_H

#include "prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubqueue
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	RenderSubqueue();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	virtual ~RenderSubqueue();

	/*!
	 * \brief Метод отрисовки.
	 */
	virtual void render();

	/*!
	 * \brief Устанавливает индекс группы.
	 */
	virtual void setGroupIdx(u32 groupIdx) { _group = groupIdx; }

	/*!
	 * \brief Получает индекс группы.
	 */
	virtual u32 getGroupIdx() const { return _group; }

private:
	u32 _group; /*!< Индекс группы подочереди. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUE_H