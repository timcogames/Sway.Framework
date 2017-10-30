#ifndef SWAY_MATH_SIZE_H
#define SWAY_MATH_SIZE_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления размера.
 */
template <typename type_t>
class TSize final {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TSize() {
		_w = _h = (type_t)0;
	}

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	explicit TSize(type_t w, type_t h) {
		set(w, h);
	}

	explicit TSize(type_t scalar) {
		set(scalar, scalar);
	}

	explicit TSize(const type_t *ptr) {
		set(ptr[0], ptr[1]);
	}

	TSize(const TSize<type_t> &flatten) {
		set(flatten.getW(), flatten.getH());
	}

	/*!
	 * \brief
	 *   Устанавливает новые значения.
	 *
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	void set(type_t w, type_t h) {
		_w = w;
		_h = h;
	}

	/*!
	 * \brief
	 *   Устанавливает значение ширины.
	 * 
	 * \param[in] w
	 *   Новое значение ширины.
	 *
	 * \sa
	 *   TSize::setH(type_t)
	 */
	void setW(type_t w) {
		_w = w;
	}

	/*!
	 * \brief
	 *   Получает значение ширины.
	 *
	 * \sa
	 *   TSize::getH()
	 */
	type_t getW() const {
		return _w;
	}

	/*!
	 * \brief
	 *   Устанавливает значение высоты.
	 * 
	 * \param[in] h
	 *   Новое значение высоты.
	 *
	 * \sa
	 *   TSize::setW(type_t)
	 */
	void setH(type_t h) {
		_h = h;
	}

	/*!
	 * \brief
	 *   Получает значение высоты.
	 *
	 * \sa
	 *   TSize::getW()
	 */
	type_t getH() const {
		return _h;
	}

	/*!
	 * \brief
	 *   Преобразовывает в TRect<type_t> класс.
	 */
	TRect<type_t> toRect() const {
		return TRect<type_t>((type_t)0, (type_t)0, _w, _h);
	}

	/*!
	 * \brief 
	 *   Оператор равенства. 
	 */
	template <typename other>
	bool operator==(const TSize<other> &compare) const {
		return _w == compare.getW() AND _h == compare.getH();
	}

	/*!
	 * \brief 
	 *   Оператор неравенства. 
	 */
	template <typename other>
	bool operator!=(const TSize<other> &compare) const {
		return !operator==(compare);
	}

private:
	type_t _w, _h;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#include "size.inl"

#endif // SWAY_MATH_SIZE_H