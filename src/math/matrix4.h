#ifndef SWAY_MATH_MATRIX4_H
#define SWAY_MATH_MATRIX4_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления матрицы.
 */
template<typename type_t>
class TMatrix4 final {
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TMatrix4() {
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
	void set(u32 row, u32 col, type_t value) {
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
	type_t get(u32 row, u32 col) const {
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
	void setRow(u32 i, const TVector4<type_t> &value) {
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
	TVector4<type_t> getRow(u32 i) const {
		return TVector4<type_t>(get(i, 0), get(i, 1), get(i, 2), get(i, 3));
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
	void setCol(u32 i, const TVector4<type_t> &value) {
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
	TVector4<type_t> getCol(u32 i) const {
		return TVector4<type_t>(get(0, i), get(1, i), get(2, i), get(3, i));
	}

	/*!
	 * \brief 
	 *   Обнуляет все элементы матрицы.
	 */
	TMatrix4<type_t> &makeZero() {
		memset(_values, 0, sizeof(type_t) * 16);
		
		return *this;
	}
	
	/*!
	 * \brief 
	 *   Приводит к единичной матрице.
	 */
	TMatrix4<type_t> &makeIdentity() {
		makeZero();
		set(0, 0, (type_t)1);
		set(1, 1, (type_t)1);
		set(2, 2, (type_t)1);
		set(3, 3, (type_t)1);

		return *this;
	}

	type_t *get() {
		return _values;
	}
	
	const type_t *get() const {
		return _values;
	}

private:
	type_t _values[16]; /*!< Элементы матрицы. */
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_MATRIX4_H