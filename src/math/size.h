#ifndef SWAY_MATH_SIZE_H
#define SWAY_MATH_SIZE_H

#include "mathprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

/*!
 * \brief
 *   Шаблонный класс представления размера.
 */
template <typename type>
class TSize final
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TSize()
	{
		set((type)0, (type)0);
	}

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	explicit TSize(type w, type h)
	{
		set(w, h);
	}

	explicit TSize(type scalar)
	{
		set(scalar, scalar);
	}

	explicit TSize(const type *ptr)
	{
		set(ptr[0], ptr[1]);
	}

	TSize(const TSize<type> &flatten)
	{
		set(flatten.getW(), flatten.getH());
	}

	/*!
	 * \brief
	 *   Устанавливает новые значения.
	 *
	 * \param w
	 *   Значение ширины.
	 * 
	 * \param h
	 *   Значение высоты.
	 */
	void set(type w, type h)
	{
		_w = w;
		_h = h;
	}

	/*!
	 * \brief
	 *   Устанавливает значение ширины.
	 * 
	 * \param w
	 *   Новое значение ширины.
	 *
	 * \sa
	 *   TSize::setH(type)
	 */
	void setW(type w)
	{
		_w = w;
	}

	/*!
	 * \brief
	 *   Получает значение ширины.
	 *
	 * \sa
	 *   TSize::getH()
	 */
	type getW() const { return _w; }

	/*!
	 * \brief
	 *   Устанавливает значение высоты.
	 * 
	 * \param h
	 *   Новое значение высоты.
	 *
	 * \sa
	 *   TSize::setW(type)
	 */
	void setH(type h)
	{
		_h = h;
	}

	/*!
	 * \brief
	 *   Получает значение высоты.
	 *
	 * \sa
	 *   TSize::getW()
	 */
	type getH() const { return _h; }

	/*!
	 * \brief
	 *   Преобразовывает в TRect<type> класс.
	 */
	TRect<type> toRect() const
	{
		return TRect<type>((type)0, (type)0, _w, _h);
	}

	/*!
	 * \brief 
	 *   Оператор равенства. 
	 */
	template <typename other>
	bool operator==(const TSize<other> &compare) const
	{
		return _w == compare.getW() AND _h == compare.getH();
	}

	/*!
	 * \brief 
	 *   Оператор неравенства. 
	 */
	template <typename other>
	bool operator!=(const TSize<other> &compare) const
	{
		return !operator==(compare);
	}

private:
	type _w, _h;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#include "size.inl"

#endif // SWAY_MATH_SIZE_H