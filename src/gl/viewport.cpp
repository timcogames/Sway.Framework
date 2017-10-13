#include "viewport.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Viewport::Viewport()
{
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Viewport::~Viewport()
{
	// Empty
}

void Viewport::reset()
{
	s32 viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	_rect.set(viewport[0], viewport[1], viewport[2], viewport[3]);
}

/*!
 * \brief
 *   Устанавливает новые значения прямоугольной области.
 *
 * \param[in] x
 *   Значение координаты по оси X.
 * 
 * \param[in] y
 *   Значение координаты по оси Y.
 * 
 * \param[in] w
 *   Значение ширины.
 * 
 * \param[in] h
 *   Значение высоты.
 */
void Viewport::set(s32 x, s32 y, s32 w, s32 h)
{
	if (_rect.getL() != x OR _rect.getT() != y OR _rect.getW() != w OR _rect.getH() != h)
	{
		glViewport(x, y, w, h);

		_rect.set(x, y, w, h);
	}
}

/*!
 * \brief
 *   Устанавливает размер прямоугольной области.
 *
 * \param[in] w
 *   Значение ширины.
 * 
 * \param[in] h
 *   Значение высоты.
 */
void Viewport::set(s32 w, s32 h)
{
	set(0, 0, w, h);
}

/*!
 * \brief
 *   Получает размер прямоугольной области.
 */
math::TRect<s32> Viewport::get() const
{
	return _rect;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)