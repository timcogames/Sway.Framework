#ifndef SWAY_GL_VERTEXDECLARATION_H
#define SWAY_GL_VERTEXDECLARATION_H

#include "vertexelement.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class VertexDeclaration {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexDeclaration(VertexElementContainer_t elements);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~VertexDeclaration();

	VertexElementContainer_t getVertexElements() const;

	VertexElement getElementAtIndex(u32 index) const;

	u32 getElementCount() const;

	u32 getTotalSize() const;

	bool hasElement(u32 stream, u32 semantic, u32 dataType) const;

private:
	VertexElementContainer_t _elements;
	u32 _totalSize;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXDECLARATION_H