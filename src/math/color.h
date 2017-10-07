#ifndef SWAY_MATH_COLOR_H
#define SWAY_MATH_COLOR_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \class
 *   TColor
 * 
 * \brief
 *   Шаблонный класс представления цвета.
 */
template<typename type>
class TColor final
{
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TColor()
	{
		set((type)0, (type)0, (type)0);
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param r
	 *   Значение канала красного цвета.
	 * 
	 * \param g
	 *   Значение канала зеленого цвета.
	 * 
	 * \param b
	 *   Значение канала синего цвета.
	 * 
	 * \param a
	 *   Значение альфа-канала.
	 */
	explicit TColor(type r, type g, type b, type a = (type)1)
	{
		set(r, g, b, a);
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения.
	 *
	 * \param r
	 *   Значение канала красного цвета.
	 * 
	 * \param g
	 *   Значение канала зеленого цвета.
	 * 
	 * \param b
	 *   Значение канала синего цвета.
	 * 
	 * \param a
	 *   Значение альфа-канала.
	 */
	void set(type r, type g, type b, type a = (type)1)
	{
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}

	/*!
	 * \brief
	 *   Получает значение канала красного цвета.
	 *
	 * \sa
	 *   TRect::getG() const
	 *   TRect::getB() const
	 *   TRect::getA() const
	 */
	type getR() const
	{
		return _r;
	}

	/*!
	 * \brief
	 *   Получает значение канала зеленого цвета.
	 *
	 * \sa
	 *   TRect::getR() const
	 *   TRect::getB() const
	 *   TRect::getA() const
	 */
	type getG() const
	{
		return _g;
	}

	/*!
	 * \brief
	 *   Получает значение канала синего цвета.
	 *
	 * \sa
	 *   TRect::getR() const
	 *   TRect::getG() const
	 *   TRect::getA() const
	 */
	type getB() const
	{
		return _b;
	}

	/*!
	 * \brief
	 *   Получает значение альфа-канала.
	 *
	 * \sa
	 *   TRect::getR() const
	 *   TRect::getG() const
	 *   TRect::getB() const
	 */
	type getA() const
	{
		return _a;
	}

private:
	type _r, _g, _b, _a;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_COLOR_H