#ifndef SWAY_MATH_VECTOR2_H
#define SWAY_MATH_VECTOR2_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления вектора из четырех компонентов.
 */
template<typename type_t>
class TVector2 final {
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TVector2() {
		_x = _y = (type_t)0;
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
	 */
	explicit TVector2(type_t x, type_t y) {
		set(x, y);
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
	 */
	void set(type_t x, type_t y) {
		_x = x;
		_y = y;
	}

	/*!
	 * \brief
	 *   Получает значение X компонента.
	 *
	 * \sa
	 *   getY() const
	 */
	type_t getX() const {
		return _x;
	}

	/*!
	 * \brief
	 *   Получает значение Y компонента.
	 *
	 * \sa
	 *   getX() const
	 */
	type_t getY() const {
		return _y;
	}

private:
	type_t _x, _y;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_VECTOR2_H