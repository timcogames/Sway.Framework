#ifndef SWAY_GL_SHADERPROGRAM_H
#define SWAY_GL_SHADERPROGRAM_H

#include "shadertypes.h"

#include "../math/math.h"
#include "../defines.h"
#include "../types.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector> // std::vector
#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::cout, std::ios
#include <algorithm> // std::for_each
#include <map> // std::map
#include <unordered_map> // std::unordered_map

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

template <typename type>
using UniformContainer = std::unordered_map<std::string, type>;

class ShaderProgram
{
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderProgram();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~ShaderProgram();

	std::string readFile(lpcstr filename);

	/*!
	 * \brief
	 *   Создает шейдерную программу.
	 */
	void create();

	void destroy();

	u32 compile(ShaderTypes type, std::string shaderStr);

	void attach(std::vector<u32> shaders);

	void detach(std::vector<u32> shaders);
	
	void link();
	
	void validate();

	void use();

	void unuse();

	void setUniformVector4(const std::string &uniform, const math::TVector4<float> &vector4);
	
	void setUniformColor(const std::string &uniform, const math::TColor<float> &color);

private:
	void _printProgramLog();

	void _printShaderLog(u32 shader);

private:
	u32 _program;
	u32 _vertexShader;
	u32 _fragmentShader;

	UniformContainer<math::TVector4<float>> _uniformVec4fSets;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERPROGRAM_H