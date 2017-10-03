#ifndef SWAY_MATH_POINT_H
#define SWAY_MATH_POINT_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template<typename type>
class TPoint final
{
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TPoint()
	{
		set((type)0, (type)0);
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param x
	 *   Значение координаты по оси X.
	 * 
	 * \param y
	 *   Значение координаты по оси Y.
	 */
	explicit TPoint(type x, type y)
	{
		set(x, y);
	}

	explicit TPoint(type scalar)
	{
		set(scalar, scalar);
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения.
	 *
	 * \param x 
	 *   Значение координаты по оси X.
	 * 
	 * \param y 
	 *   Значение координаты по оси Y.
	 */
	void set(type x, type y)
	{
		_x = x;
		_y = y;
	}

	/*!
	 * \brief 
	 *   Устанавливает новое значение координаты по оси X.
	 *
	 * \param x 
	 *   Значение координаты по оси X.
	 *
	 * \sa 
	 *   TPoint::setY() const
	 */
	void setX(type x)
	{
		_x = x;
	}

	/*!
	 * \brief 
	 *   Получает значение координаты по оси X.
	 *
	 * \sa 
	 *   TPoint::getY() const
	 */
	type getX() const
	{
		return _x;
	}

	/*!
	 * \brief 
	 *   Устанавливает новое значение координаты по оси Y.
	 *
	 * \param y 
	 *   Значение координаты по оси Y.
	 *
	 * \sa 
	 *   TPoint::setX() const
	 */
	void setY(type y)
	{
		_y = y;
	}

	/*!
	 * \brief 
	 *   Получает значение координаты по оси Y.
	 *
	 * \sa 
	 *   TPoint::getX() const
	 */
	type getY() const
	{
		return _y;
	}

	/*!
	 * \brief 
	 *   Оператор равенства. 
	 */
	template <typename other>
	bool operator==(const TPoint<other> &compare) const
	{
		return _x == compare.getX() AND _y == compare.getY();
	}

	/*!
	 * \brief 
	 *   Оператор неравенства. 
	 */
	template <typename other>
	bool operator!=(const TPoint<other> &compare) const
	{
		return !operator==(compare);
	}

private:
	type _x, _y;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_POINT_H