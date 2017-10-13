#ifndef SWAY_MATH_VECTOR4_H
#define SWAY_MATH_VECTOR4_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления вектора из четырех компонентов.
 */
template<typename type>
class TVector4 final
{
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TVector4()
	{
		_x = _y = _z = _w = (type)0;
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param[in] x
	 *   Компонент X вектора.
	 * 
	 * \param[in] y
	 *   Компонент Y вектора.
	 * 
	 * \param[in] z
	 *   Компонент Z вектора.
	 * 
	 * \param[in] w
	 *   Компонент W вектора.
	 */
	explicit TVector4(type x, type y, type z, type w)
	{
		set(x, y, z, w);
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения.
	 *
	 * \param[in] x
	 *   Значение X компонента.
	 * 
	 * \param[in] y
	 *   Значение Y компонента.
	 * 
	 * \param[in] z
	 *   Значение Z компонента.
	 * 
	 * \param[in] w
	 *   Значение W компонента.
	 */
	void set(type x, type y, type z, type w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	/*!
	 * \brief
	 *   Получает значение X компонента.
	 *
	 * \sa
	 *   TRect::getY() const
	 *   TRect::getZ() const
	 *   TRect::getW() const
	 */
	type getX() const
	{
		return _x;
	}

	/*!
	 * \brief
	 *   Получает значение Y компонента.
	 *
	 * \sa
	 *   TRect::getX() const
	 *   TRect::getZ() const
	 *   TRect::getW() const
	 */
	type getY() const
	{
		return _y;
	}

	/*!
	 * \brief
	 *   Получает значение Z компонента.
	 *
	 * \sa
	 *   TRect::getX() const
	 *   TRect::getY() const
	 *   TRect::getW() const
	 */
	type getZ() const
	{
		return _z;
	}

	/*!
	 * \brief
	 *   Получает значение W компонента.
	 *
	 * \sa
	 *   TRect::getX() const
	 *   TRect::getY() const
	 *   TRect::getZ() const
	 */
	type getW() const
	{
		return _w;
	}

private:
	type _x, _y, _z, _w;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_VECTOR4_H