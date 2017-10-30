#ifndef SWAY_MATH_RECT_H
#define SWAY_MATH_RECT_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления прямоугольной области.
 */
template<typename type_t>
class TRect final {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TRect() {
		_l = _t = _r = _b = (type_t)0;
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
	 * 
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	explicit TRect(type_t x, type_t y, type_t w, type_t h) {
		set(x, y, w, h);
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
	 * 
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	void set(type_t x, type_t y, type_t w, type_t h) {
		_l = x;
		_t = y;
		_r = x + w;
		_b = y + h;
	}

	/*!
	 * \brief
	 *   Устанавливает смещение прямоугольной области.
	 *
	 * \param[in] x
	 *   Значение координаты по оси X.
	 * 
	 * \param[in] y
	 *   Значение координаты по оси Y.
	 */
	void offset(type_t x, type_t y) {
		_l += x;
		_t += y;
		_r += x;
		_b += y;
	}

	/*!
	 * \brief
	 *   Устанавливает новое значение позиции прямоугольной области по оси X.
	 *
	 * \param[in] x
	 *   Значение координаты позиции по оси X.
	 *
	 * \sa
	 *   TRect::setT() const
	 *   TRect::setR() const
	 *   TRect::setB() const
	 *   TRect::setW() const
	 *   TRect::setH() const
	 */
	void setL(type_t x) {
		_l = x;
	}

	type_t getL() const {
		return _l;
	}

	/*!
	 * \brief
	 *   Устанавливает новое значение позиции прямоугольной области по оси Y.
	 *
	 * \param[in] x
	 *   Значение координаты позиции по оси Y.
	 *
	 * \sa
	 *   TRect::setL() const
	 *   TRect::setR() const
	 *   TRect::setB() const
	 *   TRect::setW() const
	 *   TRect::setH() const
	 */
	void setT(type_t y) {
		_t = y;
	}

	type_t getT() const {
		return _t;
	}

	void setR(type_t w) {
		_r = w;
	}

	type_t getR() const {
		return _r;
	}

	void setB(type_t h) {
		_b = h;
	}

	type_t getB() const {
		return _b;
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
	type_t getW() const {
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
	type_t getH() const {
		return _b - _t;
	}

	/*!
	 * \brief
	 *   Преобразовывает в TSize<type_t> класс.
	 */
	TSize<type_t> toSize() const {
		return TSize<type_t>(getW(), getH());
	}

	bool isEmpty() const {
		return ((getW() <= (type_t)0) OR (getH() <= (type_t)0));
	}

	bool isValid() const {
		return ((_t > _b) OR (_l > _r)) ? false : false;
	}

private:
	type_t _l, _t, _r, _b;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_RECT_H