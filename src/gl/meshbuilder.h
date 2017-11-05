#ifndef SWAY_GL_MESHBUILDER_H
#define SWAY_GL_MESHBUILDER_H

#include "shaderprogram.h"
#include "hardwarebufferdescription.h"
#include "hardwarebuffertargets.h"
#include "primitivetopologies.h"
#include "typeutils.h"

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct HardwareBufferSet {
	HardwareBuffer *vbo;
	HardwareBuffer *ibo;
};

struct MeshDescription {
	bool indexed;
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

	void create(const MeshCreateInfo &info, ShaderProgram *shader, VertexElementContainer_t vertexElements);

	/*!
	 * \brief
	 *   Выводит примитивы.
	 */
	void draw();

	u32 getTopology() const;

	bool hasIndexes() const;

	/*!
	 * \brief
	 *   Получает вершинный буфер.
	 * 
	 * \return
	 *   Вершинный буфер.
	 * 
	 * \sa
	 *   MeshBuilder::getIndexBuffer()
	 */
	HardwareBuffer *getVertexBuffer();

	/*!
	 * \brief
	 *   Получает буфер индексов.
	 * 
	 * \return
	 *   Буфер индексов.
	 * 
	 * \sa
	 *   MeshBuilder::getVertexBuffer()
	 */
	HardwareBuffer *getIndexBuffer();

private:
	/*!
	 * \brief
	 *   Выводит индексные примитивы по данным в массивах.
	 * 
	 * \sa
	 *   MeshBuilder::_drawPrimitives()
	 */
	void _drawIndexedPrimitives();

	/*!
	 * \brief
	 *   Выводит примитивы по данным в массивах.
	 * 
	 * \sa
	 *   MeshBuilder::_drawIndexedPrimitives()
	 */
	void _drawPrimitives();

private:
	HardwareBufferSet _bufferSet;
	VertexAttributeBinding *_vertexAttributeBinding;
	bool _indexed;
	GLenum _topology; /*!< Способ соединения вершин примитива между собой. */

	s32 _maxElementsVertices;
	s32 _maxElementsIndices;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_MESHBUILDER_H