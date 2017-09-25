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
	void set(T x, T y, T w, T h)
	{
		_l = x;
		_t = y;
		_r = w;
		_b = h;
	}

	void offset(T x, T y)
	{
		_l += x;
		_t += y;
		_r += x;
		_b += y;
	}

	/*!
	 * \brief Устанавливает новое значение позиции прямоугольной области по оси X.
	 *
	 * \param x Значение координаты позиции по оси X.
	 *
	 * \sa TRect::setT() const, TRect::setR() const, TRect::setB() const, TRect::setW() const, TRect::setH() const
	 */
	void setL(T x)
	{
		_l = x;
	}

	T getL() const
	{
		return _l;
	}

	/*!
	 * \brief Устанавливает новое значение позиции прямоугольной области по оси Y.
	 *
	 * \param x Значение координаты позиции по оси Y.
	 *
	 * \sa TRect::setL() const, TRect::setR() const, TRect::setB() const, TRect::setW() const, TRect::setH() const
	 */
	void setT(T y)
	{
		_t = y;
	}

	T getT() const
	{
		return _t;
	}

	void setR(T w)
	{
		_r = w;
	}

	T getR() const
	{
		return _l + _r;
	}

	void setB(T h)
	{
		_b = h;
	}

	T getB() const
	{
		return _t + _b;
	}

	/*!
	 * \brief Получает ширину прямоугольной области.
	 *
	 * \sa TRect::getL() const, TRect::getT() const, TRect::getR() const, TRect::getB() const, TRect::getH() const
	 */
	T getW() const
	{
		return _r - _l;
	}

	/*!
	 * \brief Получает высоту прямоугольной области.
	 *
	 * \sa TRect::getL() const, TRect::getT() const, TRect::getR() const, TRect::getB() const, TRect::getW() const
	 */
	T getH() const
	{
		return _b - _t;
	}

	bool isEmpty() const
	{
		return ((getW() <= (T)0) OR (getH() <= (T)0));
	}

	bool isValid() const
	{
		if ((_t > _b) OR (_l > _r))
			return false;

		return true;
	}

	TSize<T> toSize() const
	{
		return TSize<T>(getW(), getH());
	}

private:
	T _l, _t, _r, _b;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_RECT_H