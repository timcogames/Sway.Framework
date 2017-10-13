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
		makeIdentity();
	}

	/*!
	 * \brief 
	 *   Устанавливает новое значение элемента матрицы.
	 * 
	 * \param[in] row
	 *   Номер ряда.
	 * 
	 * \param[in] col
	 *   Номер колонки.
	 * 
	 * \param[in] value
	 *   Значения для установки.
	 */
	void set(u32 row, u32 col, type value)
	{
		_values[row * 4 + col] = value;
	}

	/*!
	 * \brief 
	 *   Получает значение элемента матрицы.
	 * 
	 * \param[in] row
	 *   Номер ряда.
	 * 
	 * \param[in] col
	 *   Номер колонки.
	 * 
	 * \return
	 *   Значения элемента.
	 */
	type get(u32 row, u32 col) const
	{
		return _values[row * 4 + col];
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения элементов матрицы в указанном ряду.
	 * 
	 * \param[in] i
	 *   Номер ряда.
	 * 
	 * \param[in] value
	 *   Значения для установки.
	 */
	void setRow(u32 i, const TVector4<type> &value)
	{
		set(i, 0, value.getX());
		set(i, 1, value.getY());
		set(i, 2, value.getZ());
		set(i, 3, value.getW());
	}

	/*!
	 * \brief 
	 *   Получает значения элементов матрицы в указанном ряду.
	 * 
	 * \param[in] i
	 *   Номер ряда.
	 * 
	 * \return
	 *   Значения элементов.
	 */
	TVector4<type> getRow(u32 i) const
	{
		return TVector4<type>(get(i, 0), get(i, 1), get(i, 2), get(i, 3));
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения элементов матрицы в указанной колонке.
	 * 
	 * \param[in] i
	 *   Номер колонки.
	 * 
	 * \param[in] value
	 *   Значения для установки.
	 */
	void setCol(u32 i, const TVector4<type> &value)
	{
		set(0, i, value.getX());
		set(1, i, value.getY());
		set(2, i, value.getZ());
		set(3, i, value.getW());
	}

	/*!
	 * \brief 
	 *   Получает значения элементов матрицы в указанной колонке.
	 * 
	 * \param[in] i
	 *   Номер колонки.
	 * 
	 * \return
	 *   Значения элементов.
	 */
	TVector4<type> getCol(u32 i) const
	{
		return TVector4<type>(get(0, i), get(1, i), get(2, i), get(3, i));
	}

	/*!
	 * \brief 
	 *   Обнуляет все элементы матрицы.
	 */
	TMatrix4<type> &makeZero()
	{
		memset(_values, 0, sizeof(type) * 16);
		
		return *this;
	}
	
	/*!
	 * \brief 
	 *   Приводит к единичной матрице.
	 */
	TMatrix4<type> &makeIdentity()
	{
		makeZero();
		set(0, 0, (type)1);
		set(1, 1, (type)1);
		set(2, 2, (type)1);
		set(3, 3, (type)1);

		return *this;
	}

	type *get()
	{
		return _values;
	}
	
	const type *get() const
	{
		return _values;
	}

private:
	type _values[16]; /*!< Элементы матрицы. */
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATRIX4_H