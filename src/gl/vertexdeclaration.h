#ifndef SWAY_GL_VERTEXDECLARATION_H
#define SWAY_GL_VERTEXDECLARATION_H

#include "vertexelement.h"
#include "vertexelementsemantics.h"
#include "vertexdatatypes.h"

#include "../defines.h"
#include "../types.h"

#include <vector>
#include <GL/gl.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

typedef std::vector<VertexElement> VertexElementContainer;

class VertexDeclaration
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	VertexDeclaration(VertexElementContainer elements);

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~VertexDeclaration();

	VertexElementContainer getVertexElements() const;

	VertexElement getElementAtIndex(u32 index) const;

	u32 getElementCount() const;

	u32 getTotalSize() const;

	bool hasElement(u32 stream, VertexElementSemantics semantic, VertexDataTypes dataType) const;

private:
	VertexElementContainer _elements;
	u32 _totalSize;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXDECLARATION_H