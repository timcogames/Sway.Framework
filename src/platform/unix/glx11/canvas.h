#ifndef SWAY_PLATFORM_UNIX_GLX11_CANVAS_H
#define SWAY_PLATFORM_UNIX_GLX11_CANVAS_H

#include "glx11prereqs.h"
#include "windowconfig.h"

#include "rendercontext.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	Canvas();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	~Canvas();

	/*!
	 * \brief Создает окно.
	 *
	 * \param config Конфигурация окна.
	 */
	void create(const WindowConfig &config);

	/*!
	 * \brief Уничтожает окно.
	 */
	void destroy();

	/*!
	 * \brief Обрабатывает события.
	 */
	void processEvents();

	/*!
	 * \brief Устанавливает заголовок окна.
	 *
	 * \param title Заголовок окна.
	 */
	void setTitle(lpcstr title);

	/*!
	 * \brief Устанавливает позицию окна.
	 *
	 * \param x Координата позиции окна по оси X.
	 * \param y Координата позиции окна по оси Y.
	 *
	 * \sa Canvas::getPosition(s32 *, s32 *)
	 */
	void setPosition(s32 x, s32 y);

	/*!
	 * \brief Получает позицию окна.
	 *
	 * \param x Возвращаемое значение координаты позиции окна по оси X.
	 * \param y Возвращаемое значение координаты позиции окна по оси Y.
	 *
	 * \sa Canvas::setPosition(s32, s32)
	 */
	void getPosition(s32 *x, s32 *y);

	/*!
	 * \brief Устанавливает размер окна.
	 *
	 * \param w Ширина окна.
	 * \param h Высота окна.
	 *
	 * \sa Canvas::getSize(s32 *, s32 *)
	 */
	void setSize(u32 w, u32 h);

	/*!
	 * \brief Получает размер окна.
	 *
	 * \param w Возвращаемое значение ширины окна.
	 * \param h Возвращаемое значение высоты окна.
	 *
	 * \sa Canvas::setSize(s32, s32)
	 */
	void getSize(s32 *w, s32 *h);

	/*!
	 * \brief Устанавливает поведение при смене размера.
	 *
	 * \param size Оригинальный размер окна.
	 * \param sizeHints Минимальный/максимальный размер окна.
	 * \param resizable Возможность изменения размера.
	 */
	void setSizeHints(math::TSize<s32> size, math::TSizeHints<s32> sizeHints, bool resizable);

	/*!
	 * \brief Показывает окно.
	 *
	 * \sa Canvas::hide(), Canvas::visible()
	 */
	void show();

	/*!
	 * \brief Скрывает окно.
	 *
	 * \sa Canvas::show(), Canvas::visible()
	 */
	void hide();

	/*!
	 * \brief Получает Boolean значение видимости окна.
	 *
	 * \sa Canvas::show(), Canvas::hide()
	 */
	bool visible() const;

	/*!
	 * \brief Получает уникальный идентификатор окна.
	 */
	u32 getId() const;

  private:
	bool _waitEvent(Atom atomDeleteWindow, bool keepgoing);

  private:
	::Display *_display; /*!< Идентификатор сервера. */
	::Window _root;      /*!< Идентификатор корневого окна. */
	::Window _window;    /*!< Идентификатор окна. */

	RenderContext *_context;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_CANVAS_H