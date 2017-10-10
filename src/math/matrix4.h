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
		_values[0] = (type)1; _values[4] = (type)0; _values[8]  = (type)0; _values[12] = (type)0;
		_values[1] = (type)0; _values[5] = (type)1; _values[9]  = (type)0; _values[13] = (type)0;
		_values[2] = (type)0; _values[6] = (type)0; _values[10] = (type)1; _values[14] = (type)0;
		_values[3] = (type)0; _values[7] = (type)0; _values[11] = (type)0; _values[15] = (type)1;
	}

	void set(u32 row, u32 col, type value)
	{
		_values[col + (row * 4)] = value;
	}

	type get(u32 row, u32 col) const
	{
		return _values[col + (row * 4)];
	}

private:
	type _values[16];
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATRIX4_H