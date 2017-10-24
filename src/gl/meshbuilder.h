#ifndef SWAY_GL_MESHBUILDER_H
#define SWAY_GL_MESHBUILDER_H

#include "shader.h"
#include "hardwarebufferdescription.h"
#include "hardwarebuffertargets.h"
#include "primitivetopologies.h"
#include "datatypeinfo.h"

#include "glprereqs.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct HardwareBufferSet {
	HardwareBuffer *vbo;
	HardwareBuffer *ibo;
};

struct MeshDescription {
	b32 indexed;
	u32 topology; /*!< Способ соединения вершин примитива между собой. */
};

struct MeshCreateInfo : public MeshDescription {
	struct {
		HardwareBufferCreateInfo vbo;
		HardwareBufferCreateInfo ibo;
	} buffers;
};

class MeshBuilder {
public:
	static GLenum getGLTopology(u32 topology);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	MeshBuilder(const MeshCreateInfo &info);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~MeshBuilder();

	void create(const MeshCreateInfo &info, IShader *shader, VertexElementContainer_t vertexElements);

	/*!
	 * \brief
	 *   Выводит примитивы.
	 */
	void draw();

	u32 getTopology() const;

	b32 hasIndexes() const;

	/*!
	 * \brief
	 *   Получает вершинный буфер.
	 */
	HardwareBuffer *getVertexBuffer();

	/*!
	 * \brief
	 *   Получает буфер индексов.
	 */
	HardwareBuffer *getIndexBuffer();

private:
	/*!
	 * \brief
	 *   Выводит примитивы.
	 */
	void _drawIndexedPrimitives();

	/*!
	 * \brief
	 *   Выводит примитивы.
	 */
	void _drawPrimitives();

private:
	HardwareBufferSet _bufferSet;
	VertexAttributeBinding *_vertexAttributeBinding;
	b32 _indexed;
	GLenum _topology; /*!< Способ соединения вершин примитива между собой. */

	s32 _maxElementsVertices;
	s32 _maxElementsIndices;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_MESHBUILDER_H