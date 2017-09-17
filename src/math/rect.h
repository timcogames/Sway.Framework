#ifndef SWAY_MATH_RECT_H
#define SWAY_MATH_RECT_H

#include "../defines.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template<typename T> class TSize;

template<typename T>
class TRect final
{
public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	TRect()
	{
		set((T)0, (T)0, (T)0, (T)0);
	}

	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param x Значение координаты по оси X.
	 * \param y Значение координаты по оси Y.
	 * \param w Значение ширины.
	 * \param h Значение высоты.
	 */
	explicit TRect(T x, T y, T w, T h)
	{
		set(x, y, w, h);
	}

	/*!
	 * \brief Устанавливает новые значения.
	 *
	 * \param x Значение координаты по оси X.
	 * \param y Значение координаты по оси Y.
	 * \param w Значение ширины.
	 * \param h Значение высоты.
	 */
	void set(T x, T y, T width, T height)
	{
		_left = x;
		_top = y;
		_right = width;
		_bottom = height;
	}

	void setOffset(T x, T y)
	{
		_left += x;
		_top += y;
		_right += x;
		_bottom += y;
	}

	T getL() const
	{
		return _left;
	}

	T getT() const
	{
		return _top;
	}

	T getR() const
	{
		return _left + _right;
	}

	T getB() const
	{
		return _top + _bottom;
	}

	/*!
	 * \brief Получает ширину прямоугольной области.
	 *
	 * \sa TRect::getL() const, TRect::getT() const, TRect::getR() const, TRect::getB() const, TRect::getH() const
	 */
	T getW() const
	{
		return _right - _left;
	}

	/*!
	 * \brief Получает высоту прямоугольной области.
	 *
	 * \sa TRect::getL() const, TRect::getT() const, TRect::getR() const, TRect::getB() const, TRect::getW() const
	 */
	T getH() const
	{
		return _bottom - _top;
	}

	bool isEmpty() const
	{
		return ((getW() <= (T)0) OR (getH() <= (T)0));
	}

	bool isValid() const
	{
		if ((_top > _bottom) OR (_left > _right))
			return false;

		return true;
	}

	TSize<T> toSize() const
	{
		return TSize<T>(getW(), getH());
	}

private:
	T _left, _top, _right, _bottom;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_RECT_H