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
	static GLenum getGLType(u32 type);

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
	virtual ShaderHandle_t compile(u32 type, lpcstr source);

	u32 isCompiled() const;

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

	u32 isLinked() const;
	
	/*!
	 * \brief
	 *   Проверяет программный объект.
	 */
	virtual void validate();

	u32 isValidated() const;

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

	u32 _compiled;
	u32 _linked;
	u32 _validated;

	UniformVec4fContainer_t _uniformVec4fSets;

	s32 _numActiveUniforms;
	s32 _numActiveAttributes;
	s32 _uniformMaxLength;
	s32 _attributeMaxLength;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADERBUILDER_H