#include "canvas.h"
#include "windowsizes.h"
#include "windowmodes.h"
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
 * \param params Параметры окна.
 */
void Canvas::create(const WindowInitialParams &params)
{
	_renderContext = new RenderContext();

	XVisualInfo *visualInfo = _renderContext->chooseBestFBConfig(_internalData.display);

	_internalData.rootWindow = RootWindow(_internalData.display, visualInfo->screen);

	Colormap colormap = XCreateColormap(_internalData.display, _internalData.rootWindow, visualInfo->visual, AllocNone);
	u64 windowMask = CWBorderPixel | CWColormap | CWEventMask;

	XSetWindowAttributes attrs;
	attrs.colormap = colormap;
	attrs.background_pixmap = None;
	attrs.border_pixel = 0;
	attrs.event_mask = ExposureMask | StructureNotifyMask;

	_internalData.window = XCreateWindow(_internalData.display, _internalData.rootWindow, 0, 0, 
		params.sizes[kWindowSize].getW(), params.sizes[kWindowSize].getH(), 0, visualInfo->depth, InputOutput, visualInfo->visual, windowMask, &attrs);

	if (_internalData.window == None)
		throw std::invalid_argument("Failed create window.");

	XFreeColormap(_internalData.display, colormap);
	XFree(visualInfo);

	_renderContext->createContext(_internalData.display, _internalData.window);

	XSetWMProtocols(_internalData.display, _internalData.window, &_wmDeleteWindow, 1);

	setTitle(params.title);
	setSizeHints(params.sizes, params.resizable);
}

/*!
 * \brief Уничтожает окно.
 */
void Canvas::destroy()
{
	_renderContext->destroyContext();
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
 * \sa Canvas::getPosition(s32 *, s32 *), Canvas::getPosition() const
 */
void Canvas::setPosition(s32 x, s32 y)
{
	if (NOT visible())
	{
		s64 supplied;
		XSizeHints *hints = XAllocSizeHints();
		XGetWMNormalHints(_internalData.display, _internalData.window, hints, &supplied);

		hints->flags |= PPosition;
		hints->x = hints->y = 0;

		XSetWMNormalHints(_internalData.display, _internalData.window, hints);
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
 * \sa Canvas::getPosition() const, Canvas::setPosition(s32, s32)
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
 * \brief Получает позицию окна.
 *
 * \sa Canvas::getPosition(s32 *, s32 *), Canvas::setPosition(s32, s32)
 */
math::TPoint<s32> Canvas::getPosition() const
{
	::Window dummy;
	s32 xpos, ypos;

	XTranslateCoordinates(_internalData.display, _internalData.window, _internalData.rootWindow, 0, 0, &xpos, &ypos, &dummy);

	return math::TPoint<s32>(xpos, ypos);
}

/*!
 * \brief Устанавливает размер окна.
 *
 * \param w Ширина окна.
 * \param h Высота окна.
 *
 * \sa Canvas::getSize(s32 *, s32 *), Canvas::getSize() const
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
 * \sa Canvas::getSize() const, Canvas::setSize(s32, s32)
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
 * \brief Получает размер окна.
 *
 * \sa Canvas::getSize(s32 *, s32 *), Canvas::setSize(s32, s32)
 */
math::TSize<s32> Canvas::getSize() const
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_internalData.display, _internalData.window, &attrs);

	return math::TSize<s32>(attrs.width, attrs.height);
}

void Canvas::_minSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable)
{
	hints->flags |= PMinSize;
	
	if (NOT resizable)
		goto fixed;

	if (sizes[kWindowSize_Min].getW() != DONT_CARE AND sizes[kWindowSize_Min].getH() != DONT_CARE) {
		hints->max_width = sizes[kWindowSize_Min].getW();
		hints->max_height = sizes[kWindowSize_Min].getH();
	}

	fixed:
		hints->max_width = sizes[kWindowSize].getW();
		hints->max_height = sizes[kWindowSize].getH();
}

void Canvas::_maxSize(XSizeHints *hints, const math::TSize<s32> *sizes, bool resizable) {
	hints->flags |= PMaxSize;

	if (NOT resizable)
		goto fixed;

	if (sizes[kWindowSize_Max].getW() != DONT_CARE AND sizes[kWindowSize_Max].getH() != DONT_CARE) {
		hints->max_width = sizes[kWindowSize_Max].getW();
		hints->max_height = sizes[kWindowSize_Max].getH();
	}

	fixed:
		hints->max_width = sizes[kWindowSize].getW();
		hints->max_height = sizes[kWindowSize].getH();
}

/*!
 * \brief Устанавливает поведение при смене размера.
 *
 * \param sizes Оригинальный/минимальный/максимальный размер окна.
 * \param resizable Возможность изменения размера.
 */
void Canvas::setSizeHints(const math::TSize<s32> *sizes, bool resizable) {
	XSizeHints *hints = XAllocSizeHints();
	
	_minSize(hints, sizes, resizable);
	_maxSize(hints, sizes, resizable);

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
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.type = ClientMessage;
	event.xclient.serial = 0;
	event.xclient.send_event = True;
	event.xclient.window = _internalData.window;
	event.xclient.message_type = _wmState;
	event.xclient.format = 32;
	event.xclient.data.l[0] = fullscreen ? kWindowMode_Fullscreen : kWindowMode_Windowed;
	event.xclient.data.l[1] = _wmStateFullscreen;
	event.xclient.data.l[2] = 0;

	XSendEvent(_internalData.display, _internalData.rootWindow, False, SubstructureNotifyMask | SubstructureRedirectMask, &event);
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