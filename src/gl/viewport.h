#ifndef SWAY_GL_VIEWPORT_H
#define SWAY_GL_VIEWPORT_H

#include "../math/math.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class Viewport {
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
	~Viewport();

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
	void set(s32 x, s32 y, s32 w, s32 h);

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
	void set(s32 w, s32 h);

	/*!
	 * \brief
	 *   Получает размер прямоугольной области.
	 */
	math::TRect<s32> get() const;

	/*!
	 * \brief
	 *   Получает соотношение сторон.
	 */
	float aspect() const;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VIEWPORT_H