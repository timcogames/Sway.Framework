#ifndef SWAY_GL_PRIMITIVETOPOLOGYUTILS_H
#define SWAY_GL_PRIMITIVETOPOLOGYUTILS_H

#include "../defines.h"
#include "../types.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class PrimitiveTopologyUtils
{
public:
	static GLenum toGL(PrimitiveTopologies topology)
	{
		switch (topology)
		{
		case kPrimitiveTopology_PointList:     return GL_POINTS;
		case kPrimitiveTopology_LineList:      return GL_LINES;
		case kPrimitiveTopology_LineStrip:     return GL_LINE_STRIP;
		case kPrimitiveTopology_TriangleList:  return GL_TRIANGLES;
		case kPrimitiveTopology_TriangleStrip: return GL_TRIANGLE_STRIP;
		case kPrimitiveTopology_TriangleFan:   return GL_TRIANGLE_FAN;
		default:
			return GL_TRIANGLES;
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_PRIMITIVETOPOLOGYUTILS_H