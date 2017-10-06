#ifndef SWAY_PLATFORM_UNIX_GLX11_SURFACECONTEXT_H
#define SWAY_PLATFORM_UNIX_GLX11_SURFACECONTEXT_H

#include "glx11prereqs.h"
#include <boost/noncopyable.hpp> // boost::noncopyable

#include "surfaceinternaldata.h"
#include "visualsupport.h"
#include "visualattributes.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas;

/*!
 * \class
 *   SurfaceContext
 * 
 * \brief
 *   Контекст поверхности холста.
 */
class SurfaceContext : private boost::noncopyable
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	SurfaceContext(Canvas *canvas, VisualSupport *support, s32 visualId);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~SurfaceContext();

	bool checkGLXExtension();
	bool checkGLXVersion();
	
	void printServerVendor();
	void printClientVendor();

	void printServerVersion();
	void printClientVersion();
	
	void printServerExtensions();
	void printClientExtensions();
	void printGLXExtensions();

	/*!
	 * \brief
	 *   Создает контекст визуализации.
	 */
	void create();

	/*!
	 * \brief
	 *   Уничтожает контекст визуализации.
	 */
	void destroy();

	/*!
	 * \brief
	 *   Прикрепляет контекст к окну.
	 *
	 * \sa
	 *   SurfaceContext::doneCurrent()
	 */
	bool makeCurrent();
	
	/*!
	 * \brief
	 *   Освобождаем контекст.
	 *
	 * \sa
	 *   SurfaceContext::makeCurrent()
	 */
	bool doneCurrent();

	/*!
	 * \brief
	 *   Обмен буферов.
	 */
	void present();

private:
	SurfaceInternalData _internalData;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_GLX11_SURFACECONTEXT_H