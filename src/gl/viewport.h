#ifndef SWAY_GL_VIEWPORT_H
#define SWAY_GL_VIEWPORT_H

#include "../math/rect.h"

#include "../defines.h"
#include "../types.h"

#include <GL/gl.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class Viewport
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Viewport();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Viewport();

	virtual void reset();

	/*!
	 * \brief
	 *   Устанавливает новые значения прямоугольной области.
	 *
	 * \param x
	 *   Значение координаты по оси X.
	 * 
	 * \param y
	 *   Значение координаты по оси Y.
	 * 
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	virtual void set(s32 x, s32 y, s32 w, s32 h);

	/*!
	 * \brief
	 *   Устанавливает размер прямоугольной области.
	 *
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	virtual void set(s32 w, s32 h);

	virtual math::TRect<s32> get() const;

private:
	math::TRect<s32> _rect;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VIEWPORT_H