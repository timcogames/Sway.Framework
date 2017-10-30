#ifndef SWAY_GL_VERTEXELEMENT_H
#define SWAY_GL_VERTEXELEMENT_H

#include "vertexelementsemantics.h"
#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct VertexElement {
	u16 stream;
	VertexElementSemantics semantic;
	u32 dataType;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXELEMENT_H