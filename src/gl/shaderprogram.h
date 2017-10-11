#ifndef SWAY_GL_SHADERPROGRAM_H
#define SWAY_GL_SHADERPROGRAM_H

#include "../math/math.h"
#include "shadertypes.h"
#include "glprereqs.h"

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
	 *   Создает и выполняет компиляцию шейдерного объекта.
	 * 
	 * \param type
	 *   Тип создаваемого шейдера.
	 * 
	 * \param source
	 *   Исходный код шейдера.
	 */
	u32 compile(ShaderTypes type, lpcstr source);

	/*!
	 * \brief
	 *   Связывает шейдерные объекты с программным объектом.
	 * 
	 * \param shaders
	 *   Дескрипторы связываемых шейдерных объектов.
	 */
	void attach(std::vector<u32> shaders);

	/*!
	 * \brief
	 *   Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param shaders
	 *   Дескрипторы отвязываемых шейдерных объектов.
	 */
	void detach(std::vector<u32> shaders);
	
	/*!
	 * \brief
	 *   Компоновка шей­дерных объектов.
	 */
	void link();
	
	/*!
	 * \brief
	 *   Проверяет программный объект.
	 */
	void validate();

	void use();

	void unuse();

	void setUniformVector4(const std::string &uniform, const math::TVector4<float> &vector4);
	
	void setUniformColor(const std::string &uniform, const math::TColor<float> &color);

	u32 getShaderProgram() {return _program;}

private:
	s32 _checkStatus(u32 shader, u32 name);

private:
	u32 _program;
	u32 _vertexShader;
	u32 _fragmentShader;

	UniformContainer<math::TVector4<float>> _uniformVec4fSets;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERPROGRAM_H