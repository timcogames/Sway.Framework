#include "canvas.h"
#include "windowevents.h"
#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
Canvas::Canvas()
	: _renderContext(nullptr)
{
	/* Открывает соединение с сервером. */
	_internalData.display = XOpenDisplay(nullptr);
	if (_internalData.display == nullptr)
		throw std::runtime_error("Unable to open new X connection.");

	_wmState = XInternAtom(_internalData.display, "_NET_WM_STATE", False);
	_wmStateFullscreen = XInternAtom(_internalData.display, "_NET_WM_STATE_FULLSCREEN", False);
	_wmDeleteWindow = XInternAtom(_internalData.display, "WM_DELETE_WINDOW", False);
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
Canvas::~Canvas()
{
	/* Закрываем соединение с сервером. */
	XCloseDisplay(_internalData.display);
}

/*!
 * \brief Создает окно.
 *
 * \param initialConfig Конфигурация окна.
 */
void Canvas::create(const WindowConfig &initialConfig)
{
	_internalData.config = initialConfig;

	_renderContext = new RenderContext();

	XVisualInfo *visualInfo = _renderContext->chooseBestFBConfig(_internalData.display);

	_internalData.rootWindow = RootWindow(_internalData.display, visualInfo->screen);
	_renderContext->createContext(_internalData.display);

	Colormap colormap = XCreateColormap(_internalData.display, _internalData.rootWindow, visualInfo->visual, AllocNone);
	u64 windowMask = CWBorderPixel | CWColormap | CWEventMask;

	XSetWindowAttributes attrs;
	attrs.colormap = colormap;
	attrs.background_pixmap = None;
	attrs.border_pixel = 0;
	attrs.event_mask = ExposureMask | StructureNotifyMask;

	_internalData.window = XCreateWindow(_internalData.display, _internalData.rootWindow, 0, 0, initialConfig.size.getW(), initialConfig.size.getH(),
		0, visualInfo->depth, InputOutput, visualInfo->visual, windowMask, &attrs);

	if (_internalData.window == None)
		throw std::invalid_argument("Failed create window.");

	XFreeColormap(_internalData.display, colormap);
	XFree(visualInfo);

	XSetWMProtocols(_internalData.display, _internalData.window, &_wmDeleteWindow, 1);

	setTitle(initialConfig.title);
	setSizeHints(initialConfig.size, initialConfig.sizeHints, initialConfig.resizable);
}

/*!
 * \brief Уничтожает окно.
 */
void Canvas::destroy()
{
	_renderContext->destroyContext(_internalData.display);
	SAFE_DELETE(_renderContext);

	if (_internalData.window)
	{
		XDestroyWindow(_internalData.display, _internalData.window);
		XFlush(_internalData.display);
	}
}

void Canvas::connect(WindowListener *listener)
{
	onCreate = boost::bind(&WindowListener::onCreate, listener, _1);
	onResize = boost::bind(&WindowListener::onResize, listener, _1);
	onPaint = boost::bind(&WindowListener::onPaint, listener, _1);
	onGainFocus = boost::bind(&WindowListener::onGainFocus, listener, _1);
	onLostFocus = boost::bind(&WindowListener::onLostFocus, listener, _1);
}

/*!
 * \brief Обрабатывает события.
 */
bool Canvas::eventLoop(ois::InputManager *inputManager, bool keepgoing)
{
	XEvent event = {};
	XNextEvent(_internalData.display, &event);

	if (inputManager)
	{
		if (inputManager->_keyboardUsed)
			static_cast<ois::Keyboard *>(inputManager->getObject("Keyboard"))->capture();

		if (inputManager->_mouseUsed)
			static_cast<ois::Mouse *>(inputManager->getObject("Mouse"))->capture();
	}

	switch (event.type)
	{
	case CreateNotify:
		if (onCreate)
		{
			WindowEventCreate create;
			create.position.setX(event.xcreatewindow.x);
			create.position.setY(event.xcreatewindow.y);
			create.size.setW(event.xcreatewindow.width);
			create.size.setH(event.xcreatewindow.height);

			onCreate(create);
		}
		break;

	case ConfigureNotify:
		if (onResize)
		{
			WindowEventResize resize;
			resize.size.setW(event.xconfigure.width);
			resize.size.setH(event.xconfigure.height);

			onResize(resize);
		}
		break;

	case Expose:
		if (onPaint)
		{
			WindowEventPaint paint;
			paint.position.setX(event.xexpose.x);
			paint.position.setY(event.xexpose.y);
			paint.size.setW(event.xexpose.width);
			paint.size.setH(event.xexpose.height);

			onPaint(paint);
		}
		break;

	case FocusIn:
		if (onGainFocus)
			onGainFocus(WindowEventGeneric{});
		break;

	case FocusOut:
		if (onLostFocus)
			onLostFocus(WindowEventGeneric{});
		break;

	case ClientMessage:
		if (event.xclient.format == 32 AND Atom(event.xclient.data.l[0]) == _wmDeleteWindow)
		{
			printf("exit");
			keepgoing = false;
		}
		break;
	}

	return keepgoing;
}

/*!
 * \brief Устанавливает заголовок окна.
 *
 * \param title Заголовок окна.
 */
void Canvas::setTitle(lpcstr title)
{
	XStoreName(_internalData.display, _internalData.window, title);
	XFlush(_internalData.display);
}

/*!
 * \brief Устанавливает позицию окна.
 *
 * \param x Координата позиции окна по оси X.
 * \param y Координата позиции окна по оси Y.
 *
 * \sa Canvas::getPosition(s32 *, s32 *)
 */
void Canvas::setPosition(s32 x, s32 y)
{
	if (NOT visible())
	{
		s64 supplied;
		XSizeHints *hints = XAllocSizeHints();

		if (XGetWMNormalHints(_internalData.display, _internalData.window, hints, &supplied))
		{
			hints->flags |= PPosition;
			hints->x = hints->y = 0;

			XSetWMNormalHints(_internalData.display, _internalData.window, hints);
		}

		XFree(hints);
	}

	XMoveWindow(_internalData.display, _internalData.window, x, y);
	XFlush(_internalData.display);
}

/*!
 * \brief Получает позицию окна.
 *
 * \param x Возвращаемое значение координаты позиции окна по оси X.
 * \param y Возвращаемое значение координаты позиции окна по оси Y.
 *
 * \sa Canvas::setPosition(s32, s32)
 */
void Canvas::getPosition(s32 *x, s32 *y)
{
	::Window dummy;
	s32 xpos, ypos;

	XTranslateCoordinates(_internalData.display, _internalData.window, _internalData.rootWindow, 0, 0, &xpos, &ypos, &dummy);

	if (x)
		*x = xpos;
	if (y)
		*y = ypos;
}

/*!
 * \brief Устанавливает размер окна.
 *
 * \param w Ширина окна.
 * \param h Высота окна.
 *
 * \sa Canvas::getSize(s32 *, s32 *)
 */
void Canvas::setSize(u32 w, u32 h)
{
	XResizeWindow(_internalData.display, _internalData.window, w, h);
	XFlush(_internalData.display);
}

/*!
 * \brief Получает размер окна.
 *
 * \param w Возвращаемое значение ширины окна.
 * \param h Возвращаемое значение высоты окна.
 *
 * \sa Canvas::setSize(s32, s32)
 */
void Canvas::getSize(s32 *w, s32 *h)
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.display, _internalData.window, &attrs);

	if (w)
		*w = attrs.width;
	if (h)
		*h = attrs.height;
}

/*!
 * \brief Устанавливает поведение при смене размера.
 *
 * \param size Оригинальный размер окна.
 * \param sizeHints Минимальный/максимальный размер окна.
 * \param resizable Возможность изменения размера.
 */
void Canvas::setSizeHints(math::TSize<s32> size, math::TSizeHints<s32> sizeHints, bool resizable)
{
	XSizeHints *hints = XAllocSizeHints();

	if (resizable)
	{
		if (sizeHints.min.getW() != DONT_CARE AND sizeHints.min.getH() != DONT_CARE)
		{
			hints->flags |= PMinSize;
			hints->min_width = sizeHints.min.getW();
			hints->min_height = sizeHints.min.getH();
		}

		if (sizeHints.max.getW() != DONT_CARE AND sizeHints.max.getH() != DONT_CARE)
		{
			hints->flags |= PMaxSize;
			hints->max_width = sizeHints.max.getW();
			hints->max_height = sizeHints.max.getH();
		}
	}
	else
	{
		hints->flags |= (PMinSize | PMaxSize);
		hints->min_width = hints->max_width = size.getW();
		hints->min_height = hints->max_height = size.getH();
	}

	hints->flags |= PWinGravity;
	hints->win_gravity = StaticGravity; /*!< Нет привязки. */

	XSetWMNormalHints(_internalData.display, _internalData.window, hints);
	XFree(hints);
}

/*!
 * \brief Показывает окно.
 *
 * \sa Canvas::hide(), Canvas::visible()
 */
void Canvas::show()
{
	if (NOT visible())
	{
		XMapRaised(_internalData.display, _internalData.window);
		XFlush(_internalData.display);
	}
}

/*!
 * \brief Скрывает окно.
 *
 * \sa Canvas::show(), Canvas::visible()
 */
void Canvas::hide()
{
	XUnmapWindow(_internalData.display, _internalData.window);
	XFlush(_internalData.display);
}

/*!
 * \brief Получает Boolean значение видимости окна.
 *
 * \sa Canvas::show(), Canvas::hide()
 */
bool Canvas::visible() const
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.display, _internalData.window, &attrs);
	return attrs.map_state == IsViewable;
}

/*!
 * \brief Переключает в полноэкранный/оконный режим.
 *
 * \param fullscreen Включить полноэкранный режим?
 */
void Canvas::toggleFullscreen(bool fullscreen)
{
    XWindowAttributes attrs;
    XGetWindowAttributes(_internalData.display, _internalData.window, &attrs);

    XEvent event;
    memset(&event, 0, sizeof(event));
    event.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.window = _internalData.window;
    event.xclient.message_type = _wmState;
    event.xclient.format = 32;

    if (fullscreen)
        event.xclient.data.l[0] = 1;
    else
        event.xclient.data.l[0] = 0;

    event.xclient.data.l[1] = _wmStateFullscreen;
    event.xclient.data.l[2] = 0;

    long eventMask = SubstructureRedirectMask | SubstructureNotifyMask;

    if (fullscreen)
    {
        XSendEvent(_internalData.display, _internalData.rootWindow, False, eventMask, &event);
		XMoveResizeWindow(_internalData.display, _internalData.window, 
			0, 0, _internalData.config.size.getW(), _internalData.config.size.getH());
    }
    else
    {
        XSendEvent(_internalData.display, _internalData.rootWindow, False, eventMask, &event);
		XMoveResizeWindow(_internalData.display, _internalData.window, _internalData.config.position.getX(), 
			_internalData.config.position.getY(), _internalData.config.size.getW(), _internalData.config.size.getH());
    }
}

/*!
 * \brief Получает уникальный идентификатор окна.
 */
u32 Canvas::getWindowId() const
{
	return _internalData.window;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)