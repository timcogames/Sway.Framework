#include "canvas.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief Конструктор класса.
 *
 * Выполняет инициализацию нового экземпляра класса.
 */
Canvas::Canvas()
	: _display(NULL), _window(None), _context(NULL)
{
	/* Открывает соединение с сервером. */
	_display = XOpenDisplay(NULL);
	if (_display == NULL)
		throw std::runtime_error("Unable to open new X connection.");
}

/*!
 * \brief Деструктор класса.
 *
 * Освобождает захваченные ресурсы.
 */
Canvas::~Canvas()
{
	/* Закрываем соединение с сервером. */
	XCloseDisplay(_display);
}

/*!
 * \brief Создает окно.
 *
 * \param config Конфигурация окна.
 */
void Canvas::create(const WindowConfig &config)
{
	_context = new RenderContext();
	XVisualInfo *visualInfo = _context->chooseBestFBConfig(_display);

	_root = RootWindow(_display, visualInfo->screen);
	_context->createContext(_display);
	
	Colormap colormap = XCreateColormap(_display, _root, visualInfo->visual, AllocNone);
	u64 windowMask = CWBorderPixel | CWColormap | CWEventMask;

	XSetWindowAttributes attrs;
	attrs.colormap = colormap;
	attrs.background_pixmap = None;
	attrs.border_pixel = 0;
	attrs.event_mask = ExposureMask | StructureNotifyMask;

	_window = XCreateWindow(_display, _root, 0, 0, config.size.getW(), config.size.getH(), 
		0, visualInfo->depth, InputOutput, visualInfo->visual, windowMask, &attrs);

	if (_window == None)
		throw std::invalid_argument("Failed create window.");

	XFreeColormap(_display, colormap);
	XFree(visualInfo);

	setTitle(config.title);
	setSizeHints(config.size, config.sizeHints, config.resizable);
}

/*!
 * \brief Уничтожает окно.
 */
void Canvas::destroy()
{
	_context->destroyContext(_display);

	if (_window)
	{
		XDestroyWindow(_display, _window);
		XFlush(_display);
	}
}

/*!
 * \brief Обрабатывает события.
 */
void Canvas::processEvents()
{
	Atom atomDeleteWindow = XInternAtom(_display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(_display, _window, &atomDeleteWindow, 1);

	show();

	while (_waitEvent(atomDeleteWindow, true))
	{
		if (NOT _context->makeCurrent(_display, _window))
		{
		}
		
		glClearColor(0, 0.5, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();
	
		_context->swapBuffers(_display, _window);
		
		if (NOT _context->releaseCurrent(_display))
		{
		}
	}

	hide();
}

bool Canvas::_waitEvent(Atom atomDeleteWindow, bool keepgoing)
{
	XEvent event;
	XNextEvent(_display, &event);

	if (event.type == ClientMessage)
	{
		if (event.xclient.format == 32 && event.xclient.data.l[0] == (signed)atomDeleteWindow)
			keepgoing = false;
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
	XStoreName(_display, _window, title);
	XFlush(_display);
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

		if (XGetWMNormalHints(_display, _window, hints, &supplied))
		{
			hints->flags |= PPosition;
			hints->x = hints->y = 0;

			XSetWMNormalHints(_display, _window, hints);
		}

		XFree(hints);
	}

	XMoveWindow(_display, _window, x, y);
	XFlush(_display);
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

	XTranslateCoordinates(_display, _window, _root, 0, 0, &xpos, &ypos, &dummy);

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
	XResizeWindow(_display, _window, w, h);
	XFlush(_display);
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
	XGetWindowAttributes(_display, _window, &attrs);

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

	XSetWMNormalHints(_display, _window, hints);
	XFree(hints);
}

/*!
 * \brief Показывает окно.
 *
 * \sa Canvas::hide(), Canvas::visible()
 */
void Canvas::show()
{
	if (visible())
		return;

	XMapRaised(_display, _window);
	XFlush(_display);
}

/*!
 * \brief Скрывает окно.
 *
 * \sa Canvas::show(), Canvas::visible()
 */
void Canvas::hide()
{
	XUnmapWindow(_display, _window);
	XFlush(_display);
}

/*!
 * \brief Получает Boolean значение видимости окна.
 *
 * \sa Canvas::show(), Canvas::hide()
 */
bool Canvas::visible() const
{
	XWindowAttributes attrs;
	XGetWindowAttributes(_display, _window, &attrs);
	return attrs.map_state == IsViewable;
}

/*!
 * \brief Получает уникальный идентификатор окна.
 */
u32 Canvas::getId() const
{
	return _window;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)