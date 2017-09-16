#ifndef SWAY_MATH_SIZE_H
#define SWAY_MATH_SIZE_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(math)

template <typename T>
class TSize
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	TSize()
	{
		set((T)0, (T)0);
	}

	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 *
	 * \param w Значение ширины.
	 * \param h Значение высоты.
	 */
	explicit TSize(T w, T h)
	{
		set(w, h);
	}

	/*!
	 * \brief Устанавливает новые значения.
	 *
	 * \param w Значение ширины.
	 * \param h Значение высоты.
	 */
	void set(T w, T h)
	{
		_w = w;
		_h = h;
	}

	/*!
	 * \brief Получает значение ширины.
	 *
	 * \sa getH()
	 */
	T getW() const { return _w; }

	/*!
	 * \brief Получает значение высоты.
	 *
	 * \sa getW()
	 */
	T getH() const { return _h; }

  private:
	T _w, _h;
};

NAMESPACE_END(math)
NAMESPACE_END(sway)

#endif // SWAY_MATH_SIZE_H