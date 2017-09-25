#ifndef SWAY_MATH_POINT_H
#define SWAY_MATH_POINT_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template<typename T>
class TPoint final
{
public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	TPoint()
	{
		set((T)0, (T)0);
	}

	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param x Значение координаты по оси X.
	 * \param y Значение координаты по оси Y.
	 */
	explicit TPoint(T x, T y)
	{
		set(x, y);
	}

	/*!
	 * \brief Устанавливает новые значения.
	 *
	 * \param x Значение координаты по оси X.
	 * \param y Значение координаты по оси Y.
	 */
	void set(T x, T y)
	{
		_x = x;
		_y = y;
	}

	/*!
	 * \brief Устанавливает новое значение координаты по оси X.
	 *
	 * \param x Значение координаты по оси X.
	 *
	 * \sa TPoint::setY() const
	 */
	void setX(T x)
	{
		_x = x;
	}

	/*!
	 * \brief Получает значение координаты по оси X.
	 *
	 * \sa TPoint::getY() const
	 */
	T getX() const
	{
		return _x;
	}

	/*!
	 * \brief Устанавливает новое значение координаты по оси Y.
	 *
	 * \param y Значение координаты по оси Y.
	 *
	 * \sa TPoint::setX() const
	 */
	void setY(T y)
	{
		_y = y;
	}

	/*!
	 * \brief Получает значение координаты по оси Y.
	 *
	 * \sa TPoint::getX() const
	 */
	T getY() const
	{
		return _y;
	}

private:
	T _x, _y;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_POINT_H