#ifndef SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H
#define SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H

#include "glx11prereqs.h"
#include <boost/noncopyable.hpp> // boost::noncopyable

#include "framebufferconfig.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct RenderContextInternalData
{
	::Display *xDisplay;
	u32 visualId;
	GLXFBConfig glxFBConfig;
	GLXDrawable glxDrawable;
	GLXContext glxContext;
};

class RenderContext : private boost::noncopyable
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	RenderContext();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~RenderContext();

	bool checkGLXExtension(::Display *display);

	bool checkGLXVersion(::Display *display);

	/*!
	 * \brief
	 *   Создает контекст визуализации.
	 *
	 * \param window
	 *   Идентификатор окна.
	 */
	void createContext(::Window window);

	/*!
	 * \brief
	 *   Уничтожает контекст визуализации.
	 */
	void destroyContext();

	/*!
	 * \brief
	 *   Прикрепляет контекст к окну.
	 *
	 * \sa
	 *   RenderContext::doneCurrent()
	 */
	bool makeCurrent();
	
	/*!
	 * \brief
	 *   Освобождаем контекст.
	 *
	 * \sa
	 *   RenderContext::makeCurrent()
	 */
	bool doneCurrent();

	/*!
	 * \brief
	 *   Обмен буферов.
	 */
	void present();

	XVisualInfo selectBestVisual(::Display* display);

	void chooseBestFBConfig(::Display *display);

	XVisualInfo *getVisual();
private:
	void _getMultisampleVisualConfig(GLXFBConfig fbconfig, FrameBufferConfig *config);

private:
	RenderContextInternalData _internalData;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_RENDERCONTEXT_H