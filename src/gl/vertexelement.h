#ifndef SWAY_GL_VERTEXELEMENT_H
#define SWAY_GL_VERTEXELEMENT_H

#include "vertexelementsemantics.h"
#include "vertexdatatypes.h"
#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

struct VertexElement
{
	u16 stream;
	VertexElementSemantics semantic;
	VertexDataTypes dataType;

	u32 getComponentCount() const
	{
		switch (dataType)
		{
		case kVertexDataType_Float2: return 2;
		case kVertexDataType_Float3: return 3;
		case kVertexDataType_Float4: return 4;
		default:
			return 0;
		};
	}

	u32 getElementSize() const
	{
		switch (dataType)
		{
		case kVertexDataType_Float2: return sizeof(float) * 2;
		case kVertexDataType_Float3: return sizeof(float) * 3;
		case kVertexDataType_Float4: return sizeof(float) * 4;
		default:
			return 0;
		};
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_VERTEXELEMENT_H