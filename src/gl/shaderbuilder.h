#ifndef SWAY_GL_SHADERBUILDER_H
#define SWAY_GL_SHADERBUILDER_H

#include "../math/math.h"
#include "shadertypes.h"

#include "shader.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class ShaderBuilder : public IShader {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderBuilder();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~ShaderBuilder();

	/*!
	 * \brief
	 *   Читает файл с исходным кодом шейдера.
	 * 
	 * \param[in] filename
	 *   Имя файла.
	 */
	virtual std::string readFile(lpcstr filename);

	/*!
	 * \brief
	 *   Создает и выполняет компиляцию шейдерного объекта.
	 * 
	 * \param[in] type
	 *   Тип создаваемого шейдера.
	 * 
	 * \param[in] source
	 *   Исходный код шейдера.
	 */
	virtual ShaderHandle_t compile(ShaderTypes type, lpcstr source);

	/*!
	 * \brief
	 *   Связывает шейдерные объекты с программным объектом.
	 * 
	 * \param[in] shaders
	 *   Дескрипторы связываемых шейдерных объектов.
	 */
	virtual void attach(std::vector<ShaderHandle_t> shaders);

	/*!
	 * \brief
	 *   Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param[in] shaders
	 *   Дескрипторы отвязываемых шейдерных объектов.
	 */
	virtual void detach(std::vector<ShaderHandle_t> shaders);
	
	/*!
	 * \brief
	 *   Компоновка шей­дерных объектов.
	 */
	virtual void link();
	
	/*!
	 * \brief
	 *   Проверяет программный объект.
	 */
	virtual void validate();

	virtual void use();

	virtual void unuse();

	virtual b32 isUsed() const;

	virtual void setUniformVector4(const std::string &uniform, const math::TVector4<f32> &vector4);
	
	virtual void setUniformColor(const std::string &uniform, const math::TColor<f32> &color);

	virtual ShaderProgramHandle_t getShaderProgram() const;

private:
	s32 _checkStatus(ShaderHandle_t shader, u32 name);

private:
	ShaderProgramHandle_t _program;
	ShaderHandle_t _vertexShader;
	ShaderHandle_t _fragmentShader;

	std::unordered_map<std::string, math::TVector4<f32>> _uniformVec4fSets;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERBUILDER_H