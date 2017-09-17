#ifndef SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H
#define SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H

#include "glx11prereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class RenderContext
{
  public:
	/*!
	 * \brief Конструктор класса.
	 *
	 * Выполняет инициализацию нового экземпляра класса.
	 */
	RenderContext();

	/*!
	 * \brief Деструктор класса.
	 *
	 * Освобождает захваченные ресурсы.
	 */
	~RenderContext();

	/*!
	 * \brief Создает контекст визуализации.
	 *
	 * \param display Идентификатор сервера.
	 */
	void createContext(::Display *display);

	/*!
	 * \brief Уничтожает контекст визуализации.
	 *
	 * \param display Идентификатор сервера.
	 */
	void destroyContext(::Display *display);

	/*!
	 * \brief Прикрепляет контекст к окну.
	 *
	 * \param display Идентификатор сервера.
	 * \param window Идентификатор окна.
	 * \sa RenderContext::releaseCurrent(Display *)
	 */
	bool makeCurrent(::Display *display, ::Window window);
	
	/*!
	 * \brief Освобождаем контекст.
	 *
	 * \param display Идентификатор сервера.
	 * \sa RenderContext::makeCurrent(Display *, Window)
	 */
	bool releaseCurrent(::Display *display);

	/*!
	 * \brief Обмен буферов.
	 *
	 * \param display Идентификатор сервера.
	 * \param window Идентификатор окна.
	 */
	void swapBuffers(::Display *display, ::Window window);

	XVisualInfo *chooseBestFBConfig(::Display* display);

private:
	GLXContext _context;
	GLXFBConfig _fbconfig;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H