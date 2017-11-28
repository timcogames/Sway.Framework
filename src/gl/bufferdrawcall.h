#ifndef SWAY_GL_BUFFERDRAWCALL_H
#define SWAY_GL_BUFFERDRAWCALL_H

#include "bufferobject.h"
#include "glprereqs.h"

#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct DrawElements {
	u32 mode;
	s32 count;
	u32 type;
};

struct DrawArrays {
	u32 mode;
	s32 first;
	s32 count;
};

class BufferDrawCall {
public:
	/*!
	 * \brief
	 *   Переводит тип топологии (режим отображение примитива) в GL.
	 */
	static GLenum translateTopologyToGLenum(u32 topology);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	BufferDrawCall();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~BufferDrawCall();

	void update(u32 topology, s32 count, u32 dataType, bool indexed);

	void execute(BufferObject *indexBuffer);

private:
	/*!
	 * \brief
	 *   Выводит примитивы по данным в массивах.
	 * 
	 * \sa
	 *   _drawIndexed(BufferObject *)
	 */
	void _draw(BufferObject *indexBuffer);

	/*!
	 * \brief
	 *   Выводит индексные примитивы по данным в массивах.
	 * 
	 * \sa
	 *   _draw(BufferObject *)
	 */
	void _drawIndexed(BufferObject *indexBuffer);

private:
	boost::function<void (BufferObject *)> _drawCallFunc;

	union {
		DrawElements _drawElements;
		DrawArrays _drawArrays;
	};
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_BUFFERDRAWCALL_H