#ifndef SWAY_MATH_POINT_H
#define SWAY_MATH_POINT_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления точки.
 */
template<typename type_t>
class TPoint final {
public:
	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TPoint() {
		set((type_t)0, (type_t)0);
	}

	/*!
	 * \brief 
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param[in] x
	 *   Значение координаты по оси X.
	 * 
	 * \param[in] y
	 *   Значение координаты по оси Y.
	 */
	explicit TPoint(type_t x, type_t y) {
		set(x, y);
	}

	explicit TPoint(type_t scalar) {
		set(scalar, scalar);
	}

	/*!
	 * \brief 
	 *   Устанавливает новые значения.
	 *
	 * \param[in] x 
	 *   Значение координаты по оси X.
	 * 
	 * \param[in] y 
	 *   Значение координаты по оси Y.
	 */
	void set(type_t x, type_t y) {
		_x = x;
		_y = y;
	}

	/*!
	 * \brief 
	 *   Устанавливает новое значение координаты по оси X.
	 *
	 * \param[in] x 
	 *   Значение координаты по оси X.
	 *
	 * \sa 
	 *   setY() const
	 */
	void setX(type_t x) {
		_x = x;
	}

	/*!
	 * \brief 
	 *   Получает значение координаты по оси X.
	 *
	 * \sa 
	 *   getY() const
	 */
	type_t getX() const {
		return _x;
	}

	/*!
	 * \brief 
	 *   Устанавливает новое значение координаты по оси Y.
	 *
	 * \param[in] y 
	 *   Значение координаты по оси Y.
	 *
	 * \sa 
	 *   setX() const
	 */
	void setY(type_t y) {
		_y = y;
	}

	/*!
	 * \brief 
	 *   Получает значение координаты по оси Y.
	 *
	 * \sa 
	 *   getX() const
	 */
	type_t getY() const {
		return _y;
	}

	/*!
	 * \brief 
	 *   Оператор равенства. 
	 */
	template <typename other>
	bool operator==(const TPoint<other> &compare) const {
		return _x == compare.getX() AND _y == compare.getY();
	}

	/*!
	 * \brief 
	 *   Оператор неравенства. 
	 */
	template <typename other>
	bool operator!=(const TPoint<other> &compare) const {
		return !operator==(compare);
	}

private:
	type_t _x, _y;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_POINT_H