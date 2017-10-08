#ifndef SWAY_GL_SHADERTYPEUTILS_H
#define SWAY_GL_SHADERTYPEUTILS_H

#include "shadertypes.h"
#include "../defines.h"

#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class ShaderTypeUtils
{
public:
	static ShaderTypes fromStr(const std::string &str)
	{
		if (str == "Vertex") return kShaderType_Vertex;
		else if (str == "Fragment") return kShaderType_Fragment;
		else return kShaderType_Invalid;
	}

	static GLenum toGL(ShaderTypes type)
	{
		switch (type)
		{
		case kShaderType_Vertex: return GL_VERTEX_SHADER_ARB;
		case kShaderType_Fragment: return GL_FRAGMENT_SHADER_ARB;
		default:
			return 0;
		}
	}

	static std::string toStr(ShaderTypes type)
	{
		switch (type)
		{
		CASE_TOSTRING(kShaderType_Vertex);
		CASE_TOSTRING(kShaderType_Fragment);
		default:
			return "";
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERTYPEUTILS_H