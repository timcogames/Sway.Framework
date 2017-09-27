#ifndef SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H
#define SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H

#include "glx11prereqs.h"
#include <boost/noncopyable.hpp> // boost::noncopyable

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct RenderContextData
{
	::Display *display;
	::Window window;
	GLXContext context;
};

class RenderContext : private boost::noncopyable
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
	 * \param window Идентификатор окна.
	 */
	void createContext(::Display *display, ::Window window);

	/*!
	 * \brief Уничтожает контекст визуализации.
	 */
	void destroyContext();

	/*!
	 * \brief Прикрепляет контекст к окну.
	 *
	 * \sa RenderContext::doneCurrent()
	 */
	bool makeCurrent();
	
	/*!
	 * \brief Освобождаем контекст.
	 *
	 * \sa RenderContext::makeCurrent()
	 */
	bool doneCurrent();

	/*!
	 * \brief Обмен буферов.
	 */
	void swapBuffers();

	XVisualInfo *chooseBestFBConfig(::Display *display);

private:
	RenderContextData _contextData;
	GLXFBConfig _fbconfig;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H