#ifndef SWAY_MATH_MATRIX4_H
#define SWAY_MATH_MATRIX4_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления матрицы.
 */
template<typename type>
class TMatrix4 final
{
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TMatrix4()
	{
		setRow(0, TVector4<type>(1, 0, 0, 0));
		setRow(1, TVector4<type>(0, 1, 0, 0));
		setRow(2, TVector4<type>(0, 0, 1, 0));
		setRow(3, TVector4<type>(0, 0, 0, 1));
	}

	void set(u32 row, u32 col, type value)
	{
		_values[col + (row * 4)] = value;
	}

	type get(u32 row, u32 col) const
	{
		return _values[col + (row * 4)];
	}

	void setRow(u32 i, const TVector4<type> &value)
	{
		set(i, 0, value.getX());
		set(i, 1, value.getY());
		set(i, 2, value.getZ());
		set(i, 3, value.getW());
	}

	TVector4<type> getRow(u32 i) const
	{
		return TVector4<type>(get(i, 0), get(i, 1), get(i, 2), get(i, 3));
	}

	void setCol(u32 i, const TVector4<type> &value)
	{
		set(0, i, value.getX());
		set(1, i, value.getY());
		set(2, i, value.getZ());
		set(3, i, value.getW());
	}

	TVector4<type> getCol(u32 i) const
	{
		return TVector4<type>(get(0, i), get(1, i), get(2, i), get(3, i));
	}

private:
	type _values[16];
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATRIX4_H