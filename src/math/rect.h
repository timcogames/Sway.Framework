#ifndef SWAY_MATH_RECT_H
#define SWAY_MATH_RECT_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления прямоугольной области.
 */
template<typename type>
class TRect final
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TRect()
	{
		set((type)0, (type)0, (type)0, (type)0);
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
	 * 
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	explicit TRect(type x, type y, type w, type h)
	{
		set(x, y, w, h);
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
	 * 
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	void set(type x, type y, type w, type h)
	{
		_l = x;
		_t = y;
		_r = w;
		_b = h;
	}

	void offset(type x, type y)
	{
		_l += x;
		_t += y;
		_r += x;
		_b += y;
	}

	/*!
	 * \brief
	 *   Устанавливает новое значение позиции прямоугольной области по оси X.
	 *
	 * \param x
	 *   Значение координаты позиции по оси X.
	 *
	 * \sa
	 *   TRect::setT() const
	 *   TRect::setR() const
	 *   TRect::setB() const
	 *   TRect::setW() const
	 *   TRect::setH() const
	 */
	void setL(type x)
	{
		_l = x;
	}

	type getL() const
	{
		return _l;
	}

	/*!
	 * \brief
	 *   Устанавливает новое значение позиции прямоугольной области по оси Y.
	 *
	 * \param x
	 *   Значение координаты позиции по оси Y.
	 *
	 * \sa
	 *   TRect::setL() const
	 *   TRect::setR() const
	 *   TRect::setB() const
	 *   TRect::setW() const
	 *   TRect::setH() const
	 */
	void setT(type y)
	{
		_t = y;
	}

	type getT() const
	{
		return _t;
	}

	void setR(type w)
	{
		_r = w;
	}

	type getR() const
	{
		return _l + _r;
	}

	void setB(type h)
	{
		_b = h;
	}

	type getB() const
	{
		return _t + _b;
	}

	/*!
	 * \brief
	 *   Получает ширину прямоугольной области.
	 *
	 * \sa
	 *   TRect::getL() const
	 *   TRect::getT() const
	 *   TRect::getR() const
	 *   TRect::getB() const
	 *   TRect::getH() const
	 */
	type getW() const
	{
		return _r - _l;
	}

	/*!
	 * \brief
	 *   Получает высоту прямоугольной области.
	 *
	 * \sa
	 *   TRect::getL() const
	 *   TRect::getT() const
	 *   TRect::getR() const
	 *   TRect::getB() const
	 *   TRect::getW() const
	 */
	type getH() const
	{
		return _b - _t;
	}

	bool isEmpty() const
	{
		return ((getW() <= (type)0) OR (getH() <= (type)0));
	}

	bool isValid() const
	{
		if ((_t > _b) OR (_l > _r))
			return false;

		return true;
	}

	/*!
	 * \brief
	 *   Преобразовывает в TSize<type> класс.
	 */
	TSize<type> toSize() const
	{
		return TSize<type>(getW(), getH());
	}

private:
	type _l, _t, _r, _b;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_RECT_H