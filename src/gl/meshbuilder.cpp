#include "meshbuilder.h"
#include "hardwarebuffer.h"
#include "vertexattributebinding.h"
#include "vertexdeclaration.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum MeshBuilder::getGLTopology(u32 topology) {
	switch (topology) {
	case kPrimitiveTopology_PointList: return GL_POINTS;
	case kPrimitiveTopology_LineList: return GL_LINES;
	case kPrimitiveTopology_LineStrip: return GL_LINE_STRIP;
	case kPrimitiveTopology_TriangleList: return GL_TRIANGLES;
	case kPrimitiveTopology_TriangleStrip: return GL_TRIANGLE_STRIP;
	case kPrimitiveTopology_TriangleFan: return GL_TRIANGLE_FAN;
	default: return GL_TRIANGLES;
	}
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
MeshBuilder::MeshBuilder(const MeshCreateInfo &info)
	: _topology(getGLTopology(info.topology))
	, _indexed(info.indexed) {
	/* Получаем рекомендуемое максимальное количество кэшируемых вершин. */
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &_maxElementsVertices);
	/* Получаем рекомендуемое значение максимума количества индексов. */
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &_maxElementsIndices);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
MeshBuilder::~MeshBuilder() {
	SAFE_DELETE(_vertexAttributeBinding);
	SAFE_DELETE(_bufferSet.ibo);
	SAFE_DELETE(_bufferSet.vbo);
}

void MeshBuilder::create(const MeshCreateInfo &info, IShader *shader, VertexElementContainer_t vertexElements) {
	_bufferSet.vbo = HardwareBuffer::create(info.buffers.vbo);

	_vertexAttributeBinding = new VertexAttributeBinding();
	_vertexAttributeBinding->setShader(shader);
	_vertexAttributeBinding->setVertexDeclaration(boost::make_shared<VertexDeclaration>(vertexElements));
	_vertexAttributeBinding->mergeLayout();

	if (_indexed)
		_bufferSet.ibo = HardwareBuffer::create(info.buffers.ibo);
}

/*!
 * \brief
 *   Выводит примитивы.
 */
void MeshBuilder::draw() {
	_bufferSet.vbo->bind();
	_vertexAttributeBinding->enable(_bufferSet.vbo->getByteStride());
	
	if (_indexed)
		_drawIndexedPrimitives();
	else
		_drawPrimitives();

	_vertexAttributeBinding->disable();
	_bufferSet.vbo->unbind();
}

u32 MeshBuilder::getTopology() const {
	switch (_topology) {
	case GL_POINTS: return kPrimitiveTopology_PointList;
	case GL_LINES: return kPrimitiveTopology_LineList;
	case GL_LINE_STRIP: return kPrimitiveTopology_LineStrip;
	case GL_TRIANGLES: return kPrimitiveTopology_TriangleList;
	case GL_TRIANGLE_STRIP: return kPrimitiveTopology_TriangleStrip;
	case GL_TRIANGLE_FAN: return kPrimitiveTopology_TriangleFan;
	default: return INVALID_TYPE;
	}
}

b32 MeshBuilder::hasIndexes() const {
	return _indexed;
}

/*!
 * \brief
 *   Выводит примитивы.
 */
void MeshBuilder::_drawIndexedPrimitives() {
	_bufferSet.ibo->bind();

	glDrawElements(getGLTopology(_topology), _bufferSet.ibo->getCapacity(), DataTypeInfo::toGL(_bufferSet.ibo->getDataType()), NULL);
	
	_bufferSet.ibo->unbind();
}

/*!
 * \brief
 *   Выводит примитивы.
 */
void MeshBuilder::_drawPrimitives() {
	glDrawArrays(getGLTopology(_topology), 0, _bufferSet.vbo->getCapacity());
}

/*!
 * \brief
 *   Получает вершинный буфер.
 */
HardwareBuffer *MeshBuilder::getVertexBuffer() {
	return _bufferSet.vbo;
}

/*!
 * \brief
 *   Получает буфер индексов.
 */
HardwareBuffer *MeshBuilder::getIndexBuffer() {
	return _bufferSet.ibo;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)