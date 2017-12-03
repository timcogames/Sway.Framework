#include "shaderprogram.h"
#include "shaderexception.h"
#include "extensions.h"
#include <exception>
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
ShaderProgram::ShaderProgram()
	: _linked(false)
	, _validated(false) {

	_resourceHandle = Extensions::glCreateProgramObjectARB();

	Extensions::glGetProgramivARB(_resourceHandle, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &_numActiveUniforms);
	Extensions::glGetProgramivARB(_resourceHandle, GL_OBJECT_ACTIVE_ATTRIBUTES_ARB, &_numActiveAttributes);
	Extensions::glGetProgramivARB(_resourceHandle, GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB, &_uniformMaxLength);
	Extensions::glGetProgramivARB(_resourceHandle, GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB, &_attributeMaxLength);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderProgram::~ShaderProgram() {
	std::for_each(_shaderHandleSet.begin(), _shaderHandleSet.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));
	Extensions::glDeleteProgramsARB(1, &_resourceHandle);
}

/*!
 * \brief
 *   Связывает шейдерный объект с программным объектом.
 * 
 * \param[in] shader
 *   Указатель на связываемый шейдерный объект.
 * 
 * \sa
 *   detach(ResourceHandle_t)
 */
void ShaderProgram::attach(ShaderObject *shader) {
	if (NOT shader) {
		// Empty
	}

	auto result = _shaderHandleSet.insert(shader->getHandle());
	if (result.second)
		Extensions::glAttachObjectARB(_resourceHandle, *(result.first));
}

/*!
 * \brief
 *   Отсоединяет шейдерный объект от программного объекта.
 * 
 * \param[in] shader
 *   Отвязываемый шейдерный объект.
 * 
 * \sa
 *   attach(ShaderObject *)
 */
void ShaderProgram::detach(ResourceHandle_t handle) {
	Extensions::glDetachObjectARB(_resourceHandle, handle);
	_shaderHandleSet.erase(handle);
}

/*!
 * \brief
 *   Компоновка шей­дерных объектов.
 */
void ShaderProgram::link() {
	Extensions::glLinkProgramARB(_resourceHandle);

	int linkStatus;
	Extensions::glGetObjectParameterivARB(_resourceHandle, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
	_linked = (linkStatus == GL_TRUE);
	if (NOT _linked)
		throw ShaderLinkageException(ShaderUtils::getErrorInfo(_resourceHandle));
}

bool ShaderProgram::isLinked() const {
	return _linked;
}

/*!
 * \brief
 *   Проверяет программный объект.
 */
void ShaderProgram::validate() {
	Extensions::glValidateProgramARB(_resourceHandle);
	
	int validateStatus;
	Extensions::glGetObjectParameterivARB(_resourceHandle, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
	_validated = (validateStatus == GL_TRUE);
	if (NOT _validated)
		throw ShaderValidationException(ShaderUtils::getErrorInfo(_resourceHandle));
}

bool ShaderProgram::isValidated() const {
	return _validated;
}

void ShaderProgram::use() {
	if (_resourceHandle > 0 AND NOT isUsed()) {
		Extensions::glUseProgramObjectARB(_resourceHandle);

		for (auto iter : _uniformVec4fSets) {
			s32 location = Extensions::glGetUniformLocationARB(_resourceHandle, iter.first.c_str());
			if (location != -1)
				Extensions::glUniform4fARB(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
		}
	}
}

void ShaderProgram::unuse() {
	if (_resourceHandle > 0 AND isUsed())
		Extensions::glUseProgramObjectARB(0);
}

bool ShaderProgram::isUsed() const {
	s32 current = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);

	return (current == (s32)_resourceHandle);
}

void ShaderProgram::setUniformVector4(const std::string &uniform, const math::TVector4<f32> &vector4) {
	_uniformVec4fSets[uniform] = vector4;
}

void ShaderProgram::setUniformColor(const std::string &uniform, const math::TColor<f32> &color) {
	_uniformVec4fSets[uniform] = color.toVec4();
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)