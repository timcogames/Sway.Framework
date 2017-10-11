#ifndef SWAY_GL_PRIMITIVETOPOLOGIES_H
#define SWAY_GL_PRIMITIVETOPOLOGIES_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

enum PrimitiveTopologies
{
	kPrimitiveTopology_Invalid       = 0,
	kPrimitiveTopology_PointList     = 0xFE12,
	kPrimitiveTopology_LineList      = 0xFDBE,
	kPrimitiveTopology_LineStrip     = 0x6B83,
	kPrimitiveTopology_TriangleList  = 0x7DD0,
	kPrimitiveTopology_TriangleStrip = 0x9FAE,
	kPrimitiveTopology_TriangleFan   = 0x3EAC
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_PRIMITIVETOPOLOGIES_H