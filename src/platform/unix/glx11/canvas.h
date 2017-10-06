#ifndef SWAY_PLATFORM_UNIX_GLX11_CANVAS_H
#define SWAY_PLATFORM_UNIX_GLX11_CANVAS_H

#include "glx11prereqs.h"
#include "windowinitialparams.h"
#include "windowinternaldata.h"
#include "windowlistener.h"

#include "visualsupport.h"
#include "surfacecontext.h"

#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind
#include <boost/noncopyable.hpp> // boost::noncopyable

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas : private boost::noncopyable
{
public:
	boost::function<void(const WindowEventCreate &)> onCreate;
	boost::function<void(const WindowEventResize &)> onResize;
	boost::function<void(const WindowEventRedraw &)> onRedraw;
	boost::function<void(const WindowEventGeneric &)> onGainFocus;
	boost::function<void(const WindowEventGeneric &)> onLostFocus;

public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Canvas();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Canvas();

	//x_connect
	//x_disconnect

	/*!
	 * \brief
	 *   Создает окно.
	 *
	 * \param params
	 *   Параметры окна.
	 */
	void create(const WindowInitialParams &params);

	/*!
	 * \brief
	 *   Уничтожает окно.
	 */
	void destroy();

	void connect(WindowListener *listener);

	/*!
	 * \brief
	 *   Обрабатывает события.
	 */
	bool eventLoop(ois::InputManager *inputManager, bool keepgoing);

	/*!
	 * \brief
	 *   Устанавливает заголовок окна.
	 *
	 * \param title
	 *   Заголовок окна.
	 */
	void setTitle(lpcstr title);

	/*!
	 * \brief
	 *   Устанавливает позицию окна.
	 *
	 * \param x
	 *   Координата позиции окна по оси X.
	 * 
	 * \param y
	 *   Координата позиции окна по оси Y.
	 *
	 * \sa
	 *   Canvas::getPosition(s32 *, s32 *)
	 *   Canvas::getPosition() const
	 */
	void setPosition(s32 x, s32 y);

	//!@{

	/*!
	 * \brief
	 *   Получает позицию окна.
	 *
	 * \param x
	 *   Возвращаемое значение координаты позиции окна по оси X.
	 * 
	 * \param y
	 *   Возвращаемое значение координаты позиции окна по оси Y.
	 *
	 * \sa
	 *   Canvas::getPosition() const
	 *   Canvas::setPosition(s32, s32)
	 */
	void getPosition(s32 *x, s32 *y);

	/*!
	 * \brief
	 *   Получает позицию окна.
	 *
	 * \sa
	 *   Canvas::getPosition(s32 *, s32 *)
	 *   Canvas::setPosition(s32, s32)
	 */
	math::TPoint<s32> getPosition() const;

	//!@}

	/*!
	 * \brief
	 *   Устанавливает размер окна.
	 *
	 * \param w
	 *   Ширина окна.
	 * 
	 * \param h
	 *   Высота окна.
	 *
	 * \sa
	 *   Canvas::getSize(s32 *, s32 *)
	 *   Canvas::getSize() const
	 */
	void setSize(u32 w, u32 h);

	//!@{

	/*!
	 * \brief
	 *   Получает размер окна.
	 *
	 * \param w
	 *   Возвращаемое значение ширины окна.
	 * 
	 * \param h
	 *   Возвращаемое значение высоты окна.
	 *
	 * \sa
	 *   Canvas::getSize() const
	 *   Canvas::setSize(s32, s32)
	 */
	void getSize(s32 *w, s32 *h);

	/*!
	 * \brief
	 *   Получает размер окна.
	 *
	 * \sa
	 *   Canvas::getSize(s32 *, s32 *)
	 *   Canvas::setSize(s32, s32)
	 */
	math::TSize<s32> getSize() const;

	//!@}

	/*!
	 * \brief
	 *   Устанавливает поведение при смене размера.
	 *
	 * \param sizes
	 *   Оригинальный/минимальный/максимальный размер окна.
	 * 
	 * \param resizable
	 *   Возможность изменения размера.
	 */
	void setSizeHints(const math::TSize<s32> *sizes, bool resizable);

	/*!
	 * \brief
	 *   Показывает окно.
	 *
	 * \sa
	 *   Canvas::hide()
	 *   Canvas::visible()
	 */
	void show();

	/*!
	 * \brief
	 *   Скрывает окно.
	 *
	 * \sa
	 *   Canvas::show()
	 *   Canvas::visible()
	 */
	void hide();

	/*!
	 * \brief
	 *   Получает Boolean значение видимости окна.
	 *
	 * \sa
	 *   Canvas::show()
	 *   Canvas::hide()
	 */
	bool visible() const;

	/*!
	 * \brief
	 *   Переключает в полноэкранный/оконный режим.
	 *
	 * \param fullscreen
	 *   Включить полноэкранный режим?
	 */
	void setFullscreen(bool fullscreen);

	void setMaximize(bool maximized);

	void *getXDisplay() const;

	/*!
	 * \brief
	 *   Получает уникальный идентификатор окна.
	 */
	u32 getXWindow() const;

	SurfaceContext *getContext();

private:
	void _minSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable);
	void _maxSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable);

public:
	WindowInternalData _internalData;
	VisualSupport *_support;
	SurfaceContext *_context;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_CANVAS_H