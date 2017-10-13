#ifndef SWAY_MATH_VECTOR3_H
#define SWAY_MATH_VECTOR3_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления вектора из трех компонентов.
 */
template<typename type>
class TVector3 final
{
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TVector3()
	{
		_x = _y = _z = (type)0;
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
	 */
	explicit TVector3(type x, type y, type z)
	{
		set(x, y, z);
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
	 */
	void set(type x, type y, type z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	/*!
	 * \brief
	 *   Получает значение X компонента.
	 *
	 * \sa
	 *   TRect::getY() const
	 *   TRect::getZ() const
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
	 */
	type getZ() const
	{
		return _z;
	}

private:
	type _x, _y, _z;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_VECTOR3_H