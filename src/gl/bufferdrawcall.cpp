#include "bufferdrawcall.h"
#include "primitivetopology.h"
#include "typeutils.h"

#include <boost/core/ignore_unused.hpp> // boost::ignore_unused

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Переводит тип топологии (режим отображение примитива) в GL.
 */
GLenum BufferDrawCall::translateTopologyToGLenum(u32 topology) {
	switch (topology) {
	case kPrimitiveTopology_PointList: return GL_POINTS;
	case kPrimitiveTopology_LineList: return GL_LINES;
	case kPrimitiveTopology_LineStrip: return GL_LINE_STRIP;
	case kPrimitiveTopology_TriangleList: return GL_TRIANGLES;
	case kPrimitiveTopology_TriangleStrip: return GL_TRIANGLE_STRIP;
	case kPrimitiveTopology_TriangleFan: return GL_TRIANGLE_FAN;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
BufferDrawCall::BufferDrawCall() {
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
BufferDrawCall::~BufferDrawCall() {
	// Empty
}

void BufferDrawCall::update(u32 topology, s32 count, u32 dataType, bool indexed) {
	if (indexed) {
		_drawCallFunc = boost::bind(&BufferDrawCall::_drawIndexed, this, _1);

		_drawElements.mode = BufferDrawCall::translateTopologyToGLenum(topology);
		_drawElements.count = count;
		_drawElements.type = gl::TypeUtils::toGL(dataType);
	}
	else {
		_drawCallFunc = boost::bind(&BufferDrawCall::_draw, this, _1);

		_drawArrays.mode = BufferDrawCall::translateTopologyToGLenum(topology);
		_drawArrays.first = 0;
		_drawArrays.count = count;
	}
}

void BufferDrawCall::execute(BufferObject *indexBuffer) {
	if (_drawCallFunc)
		_drawCallFunc(indexBuffer);
}

/*!
 * \brief
 *   Выводит примитивы по данным в массивах.
 * 
 * \sa
 *   _drawIndexed(BufferObject *)
 */
void BufferDrawCall::_draw(BufferObject *indexBuffer) {
	boost::ignore_unused(indexBuffer);

	glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

/*!
 * \brief
 *   Выводит индексные примитивы по данным в массивах.
 * 
 * \sa
 *   _draw(BufferObject *)
 */
void BufferDrawCall::_drawIndexed(BufferObject *indexBuffer) {
	BOOST_ASSERT(indexBuffer);

	indexBuffer->bind();
	glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, NULL);
	indexBuffer->unbind();
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)