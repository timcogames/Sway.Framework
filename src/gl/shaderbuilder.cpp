#include "shaderbuilder.h"
#include "shadertypeutils.h"
#include "extensions.h"
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

IShader *allocateShader()
{
	return new ShaderBuilder();
}

void freeShader(IShader *object)
{
	delete object;
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
ShaderBuilder::ShaderBuilder()
	: _program(0), _vertexShader(0), _fragmentShader(0)
{
	Extensions::define();

	_program = Extensions::glCreateProgramObjectARB();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderBuilder::~ShaderBuilder()
{
	if (_program > 0)
		Extensions::glDeleteProgramsARB(1, &_program);
}

/*!
 * \brief
 *   Читает файл с исходным кодом шейдера.
 * 
 * \param[in] filename
 *   Имя файла.
 */
std::string ShaderBuilder::readFile(lpcstr filename)
{
	std::ifstream fileStream(filename, std::ios::binary);
	if (NOT fileStream.is_open()) {
		printf("File %s not found\n", filename);
		return "";
	}

	std::string fileContent((std::istreambuf_iterator<s8>(fileStream)), std::istreambuf_iterator<s8>());
	fileStream.close();

	return fileContent;
}

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
ShaderHandle_t ShaderBuilder::compile(ShaderTypes type, lpcstr source)
{
	auto shader = Extensions::glCreateShaderObjectARB(ShaderTypeUtils::toGL(type));
	Extensions::glShaderSourceARB(shader, 1, &source, NULL);
	Extensions::glCompileShaderARB(shader);

	if (_checkStatus(shader, GL_OBJECT_COMPILE_STATUS_ARB)) {
		// Empty
	}

	return shader;
}

/*!
 * \brief
 *   Связывает шейдерные объекты с программным объектом.
 * 
 * \param[in] shaders
 *   Дескрипторы связываемых шейдерных объектов.
 */
void ShaderBuilder::attach(std::vector<ShaderHandle_t> shaders)
{
	for (auto shader : shaders)
		Extensions::glAttachObjectARB(_program, shader);
}

/*!
 * \brief
 *   Отсоединяет шейдерный объект от программного объекта.
 * 
 * \param[in] shaders
 *   Дескрипторы отвязываемых шейдерных объектов.
 */
void ShaderBuilder::detach(std::vector<ShaderHandle_t> shaders)
{
	for (auto shader : shaders)
		Extensions::glDetachObjectARB(_program, shader);

	std::for_each(shaders.begin(), shaders.end(), Extensions::glDeleteObjectARB);
}

/*!
 * \brief
 *   Компоновка шей­дерных объектов.
 */
void ShaderBuilder::link()
{
	Extensions::glLinkProgramARB(_program);
	if (_checkStatus(_program, GL_OBJECT_LINK_STATUS_ARB)) {
		// Empty
	}
}

/*!
 * \brief
 *   Проверяет программный объект.
 */
void ShaderBuilder::validate()
{
	Extensions::glValidateProgramARB(_program);
	if (_checkStatus(_program, GL_OBJECT_VALIDATE_STATUS_ARB)) {
		// Empty
	}
}

void ShaderBuilder::use()
{
	if (_program > 0 AND NOT isUsed()) {
		Extensions::glUseProgramObjectARB(_program);

		for (auto iter : _uniformVec4fSets)
			Extensions::glUniform4fARB(Extensions::glGetUniformLocationARB(_program, iter.first.c_str()), iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
	}
}

void ShaderBuilder::unuse()
{
	if (_program > 0 AND isUsed())
		Extensions::glUseProgramObjectARB(0);
}

b32 ShaderBuilder::isUsed() const
{
	s32 current = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);

	return (current == (s32)_program);
}

void ShaderBuilder::setUniformVector4(const std::string &uniform, const math::TVector4<f32> &vector4)
{
	_uniformVec4fSets[uniform] = vector4;
}

void ShaderBuilder::setUniformColor(const std::string &uniform, const math::TColor<f32> &color)
{
	_uniformVec4fSets[uniform] = color.toVec4();
}

ShaderProgramHandle_t ShaderBuilder::getShaderProgram() const {
	return _program;
}

s32 ShaderBuilder::_checkStatus(ShaderHandle_t shader, u32 name)
{
	int status = 0, length = 0;

	Extensions::glGetObjectParameterivARB(shader, name, &status);
	if (status == FAILURE_STATUS) {
		Extensions::glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
		if (length > 1) {
			lpstr info = (lpstr)malloc(length);
			Extensions::glGetInfoLogARB(shader, length, NULL, info);
			printf("Failed:\n%s", info);
			free(info);
		}
	}

	return status;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)