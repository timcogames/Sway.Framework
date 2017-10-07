#include "canvas.h"
#include "windowsizes.h"
#include "windowmodes.h"
#include "windowevents.h"
#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Canvas::Canvas()
	: _context(NULL)
{
	/* Открывает соединение с сервером. */
	_internalData.xDisplay = XOpenDisplay(NULL);
	if (_internalData.xDisplay == NULL)
		throw std::runtime_error("Unable to open new X connection.");

	_internalData.xAtoms[kAtom_NET_WM_STATE] = XInternAtom(_internalData.xDisplay, "_NET_WM_STATE", False);
	_internalData.xAtoms[kAtom_NET_WM_STATE_MAXIMIZED_VERT] = XInternAtom(_internalData.xDisplay, "_NET_WM_STATE_MAXIMIZED_VERT", False);
	_internalData.xAtoms[kAtom_NET_WM_STATE_MAXIMIZED_HORZ] = XInternAtom(_internalData.xDisplay, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
	_internalData.xAtoms[kAtom_NET_WM_STATE_FULLSCREEN] = XInternAtom(_internalData.xDisplay, "_NET_WM_STATE_FULLSCREEN", False);
	_internalData.xAtoms[kAtom_WM_DELETE_WINDOW] = XInternAtom(_internalData.xDisplay, "WM_DELETE_WINDOW", False);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Canvas::~Canvas()
{
	/* Закрываем соединение с сервером. */
	XCloseDisplay(_internalData.xDisplay);
}

/*!
 * \brief
 *   Создает окно.
 *
 * \param params
 *   Параметры окна.
 */
void Canvas::create(const WindowInitialParams &params)
{
	_support = new VisualSupport();

	_internalData.xVisual = _support->chooseBestSuitable(_internalData.xDisplay);
	_internalData.xScreen = XDefaultScreen(_internalData.xDisplay);
	_internalData.xRoot = RootWindow(_internalData.xDisplay, _internalData.xScreen);
	_internalData.xColormap = XCreateColormap(_internalData.xDisplay, _internalData.xRoot, _internalData.xVisual.visual, AllocNone);
	
	u64 windowMask = CWBorderPixel | CWColormap | CWEventMask;

	XSetWindowAttributes attrs;
	attrs.colormap = _internalData.xColormap;
	attrs.background_pixmap = None;
	attrs.border_pixel = 0;
	attrs.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonMotionMask | StructureNotifyMask | ExposureMask | FocusChangeMask;

	_internalData.xWindow = XCreateWindow(_internalData.xDisplay, _internalData.xRoot, 0, 0, 
		params.sizes[kWindowSize].getW(), params.sizes[kWindowSize].getH(), 0, _internalData.xVisual.depth, InputOutput, _internalData.xVisual.visual, windowMask, &attrs);

	if (_internalData.xWindow == None)
		throw std::invalid_argument("Failed create window.");

	_context = new SurfaceContext(this, _support, _internalData.xVisual.visualid);
	_context->create();

	XSetWMProtocols(_internalData.xDisplay, _internalData.xWindow, &_internalData.xAtoms[kAtom_WM_DELETE_WINDOW], 1);

	setTitle(params.title);
	setSizeHints(params.sizes, params.resizable);
}

/*!
 * \brief
 *   Уничтожает окно.
 */
void Canvas::destroy()
{
	_context->destroy();
	SAFE_DELETE(_context);

	if (_internalData.xWindow)
	{
		XDestroyWindow(_internalData.xDisplay, _internalData.xWindow);
		XFlush(_internalData.xDisplay);
	}

	if (_internalData.xColormap)
	{
		XFreeColormap(_internalData.xDisplay, _internalData.xColormap);
		_internalData.xColormap = 0;
	}
}

void Canvas::connect(WindowListener *listener)
{
	_onCreate = boost::bind(&WindowListener::onCreate, listener, _1);
	_onResize = boost::bind(&WindowListener::onResize, listener, _1);
	_onRedraw = boost::bind(&WindowListener::onRedraw, listener, _1);
	_onGainFocus = boost::bind(&WindowListener::onGainFocus, listener, _1);
	_onLostFocus = boost::bind(&WindowListener::onLostFocus, listener, _1);
}

/*!
 * \brief
 *   Обрабатывает события.
 */
bool Canvas::eventLoop(ois::InputManager *inputManager, bool keepgoing)
{
	XEvent event = {};
	XNextEvent(_internalData.xDisplay, &event);

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
		if (_onCreate)
		{
			WindowEventCreate create;
			create.position.setX(event.xcreatewindow.x);
			create.position.setY(event.xcreatewindow.y);
			create.size.setW(event.xcreatewindow.width);
			create.size.setH(event.xcreatewindow.height);

			_onCreate(create);
		}
		break;

	case ConfigureNotify:
		if (_onResize)
		{
			WindowEventResize resize;
			resize.size.setW(event.xconfigure.width);
			resize.size.setH(event.xconfigure.height);

			_onResize(resize);
		}
		break;

	case Expose:
		//needRedraw = true;
		if (_onRedraw)
		{
			WindowEventRedraw redraw;
			redraw.position.setX(event.xexpose.x);
			redraw.position.setY(event.xexpose.y);
			redraw.size.setW(event.xexpose.width);
			redraw.size.setH(event.xexpose.height);

			_onRedraw(redraw);
		}
		break;

	case FocusIn:
		if (_onGainFocus)
			_onGainFocus(WindowEventGeneric {});
		break;

	case FocusOut:
		if (_onLostFocus)
			_onLostFocus(WindowEventGeneric {});
		break;

	case ClientMessage:
		if (event.xclient.format == 32 AND Atom(event.xclient.data.l[0]) == _internalData.xAtoms[kAtom_WM_DELETE_WINDOW])
			keepgoing = false;
		break;
	}

	return keepgoing;
}

/*!
 * \brief
 *   Устанавливает заголовок окна.
 *
 * \param title
 *   Заголовок окна.
 */
void Canvas::setTitle(lpcstr title)
{
	XStoreName(_internalData.xDisplay, _internalData.xWindow, title);
	XFlush(_internalData.xDisplay);
}

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
void Canvas::setPosition(s32 x, s32 y)
{
	if (NOT visible())
	{
		s64 supplied;
		XSizeHints *hints = XAllocSizeHints();
		XGetWMNormalHints(_internalData.xDisplay, _internalData.xWindow, hints, &supplied);

		hints->flags |= PPosition;
		hints->x = hints->y = 0;

		XSetWMNormalHints(_internalData.xDisplay, _internalData.xWindow, hints);
		XFree(hints);
	}

	XMoveWindow(_internalData.xDisplay, _internalData.xWindow, x, y);
	XFlush(_internalData.xDisplay);
}

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
void Canvas::getPosition(s32 *x, s32 *y)
{
	::Window dummy;
	s32 xpos, ypos;

	XTranslateCoordinates(_internalData.xDisplay, _internalData.xWindow, _internalData.xRoot, 0, 0, &xpos, &ypos, &dummy);

	if (x)
		*x = xpos;
	if (y)
		*y = ypos;
}

/*!
 * \brief
 *   Получает позицию окна.
 *
 * \sa
 *   Canvas::getPosition(s32 *, s32 *)
 *   Canvas::setPosition(s32, s32)
 */
math::TPoint<s32> Canvas::getPosition() const
{
	::Window dummy;
	s32 xpos, ypos;

	XTranslateCoordinates(_internalData.xDisplay, _internalData.xWindow, _internalData.xRoot, 0, 0, &xpos, &ypos, &dummy);

	return math::TPoint<s32>(xpos, ypos);
}

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
void Canvas::setSize(u32 w, u32 h)
{
	XResizeWindow(_internalData.xDisplay, _internalData.xWindow, w, h);
	XFlush(_internalData.xDisplay);
}

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
void Canvas::getSize(s32 *w, s32 *h)
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.xDisplay, _internalData.xWindow, &attrs);

	if (w)
		*w = attrs.width;
	if (h)
		*h = attrs.height;
}

/*!
 * \brief
 *   Получает размер окна.
 *
 * \sa
 *   Canvas::getSize(s32 *, s32 *)
 *   Canvas::setSize(s32, s32)
 */
math::TSize<s32> Canvas::getSize() const
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.xDisplay, _internalData.xWindow, &attrs);

	return math::TSize<s32>(attrs.width, attrs.height);
}

void Canvas::_minSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable)
{
	if (resizable)
	{
		if (sizes[kWindowSize_Min].getW() != DONT_CARE AND sizes[kWindowSize_Min].getH() != DONT_CARE)
		{
			hints->min_width = sizes[kWindowSize_Min].getW();
			hints->min_height = sizes[kWindowSize_Min].getH();
		}
	}
	else
	{
		hints->min_width = sizes[kWindowSize].getW();
		hints->min_height = sizes[kWindowSize].getH();
	}
}

void Canvas::_maxSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable)
{
	if (resizable)
	{
		if (sizes[kWindowSize_Max].getW() != DONT_CARE AND sizes[kWindowSize_Max].getH() != DONT_CARE)
		{
			hints->max_width = sizes[kWindowSize_Max].getW();
			hints->max_height = sizes[kWindowSize_Max].getH();
		}
	}
	else
	{
		hints->max_width = sizes[kWindowSize].getW();
		hints->max_height = sizes[kWindowSize].getH();
	}
}

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
void Canvas::setSizeHints(const math::TSize<s32> *sizes, bool resizable) {
	XSizeHints *hints = XAllocSizeHints();
	
	hints->flags |= (PMinSize | PMaxSize);

	_minSize(hints, sizes, resizable);
	_maxSize(hints, sizes, resizable);

	XSetWMNormalHints(_internalData.xDisplay, _internalData.xWindow, hints);
	XFree(hints);
}

/*!
 * \brief
 *   Показывает окно.
 *
 * \sa
 *   Canvas::hide()
 *   Canvas::visible()
 */
void Canvas::show()
{
	if (NOT visible())
	{
		XMapRaised(_internalData.xDisplay, _internalData.xWindow);
		XFlush(_internalData.xDisplay);
	}
}

/*!
 * \brief
 *   Скрывает окно.
 *
 * \sa
 *   Canvas::show()
 *   Canvas::visible()
 */
void Canvas::hide()
{
	XUnmapWindow(_internalData.xDisplay, _internalData.xWindow);
	XFlush(_internalData.xDisplay);
}

/*!
 * \brief
 *   Получает Boolean значение видимости окна.
 *
 * \sa
 *   Canvas::show()
 *   Canvas::hide()
 */
bool Canvas::visible() const
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.xDisplay, _internalData.xWindow, &attrs);
	return attrs.map_state == IsViewable;
}

/*!
 * \brief
 *   Переключает в полноэкранный/оконный режим.
 *
 * \param fullscreen
 *   Включить полноэкранный режим?
 */
void Canvas::setFullscreen(bool fullscreen)
{
	XEvent event;
	event.type = ClientMessage;
	event.xclient.serial = 0;
	event.xclient.send_event = True;
	event.xclient.window = _internalData.xWindow;
	event.xclient.message_type = _internalData.xAtoms[kAtom_NET_WM_STATE];
	event.xclient.format = 32;
	event.xclient.data.l[0] = fullscreen ? kWindowMode_Fullscreen : kWindowMode_Windowed;
	event.xclient.data.l[1] = _internalData.xAtoms[kAtom_NET_WM_STATE_FULLSCREEN];
	event.xclient.data.l[2] = 0;

	XSendEvent(_internalData.xDisplay, _internalData.xRoot, False, SubstructureNotifyMask | SubstructureRedirectMask, &event);
}

void Canvas::setMaximize(bool maximized)
{
	XEvent event;
	event.xclient.type = ClientMessage;
	event.xclient.window = _internalData.xWindow;
	event.xclient.message_type = _internalData.xAtoms[kAtom_NET_WM_STATE];
	event.xclient.format = 32;
	event.xclient.data.l[0] = maximized ? 1 : 0;
	event.xclient.data.l[1] = 0;
	event.xclient.data.l[2] = 0;
	
	int i = 1;
	event.xclient.data.l[i++] = _internalData.xAtoms[kAtom_NET_WM_STATE_MAXIMIZED_VERT];
	event.xclient.data.l[i++] = _internalData.xAtoms[kAtom_NET_WM_STATE_MAXIMIZED_HORZ];

	XSendEvent(_internalData.xDisplay, _internalData.xRoot, False, SubstructureRedirectMask, &event);
}

void *Canvas::getXDisplay() const
{
	return _internalData.xDisplay;
}

/*!
 * \brief
 *   Получает уникальный идентификатор окна.
 */
u32 Canvas::getXWindow() const
{
	return _internalData.xWindow;
}

SurfaceContext *Canvas::getContext()
{
	return _context;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)