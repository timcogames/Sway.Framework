#include "shaderprogram.h"
#include "shadertypeutils.h"
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glCreateProgramObjectARB");
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glCreateShaderObjectARB");
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) glXGetProcAddressARB((const GLubyte*) "glShaderSourceARB");
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) glXGetProcAddressARB((const GLubyte*) "glCompileShaderARB");
PFNGLATTACHOBJECTARBPROC glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glAttachObjectARB");
PFNGLLINKPROGRAMARBPROC glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) glXGetProcAddressARB((const GLubyte*) "glLinkProgramARB");
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glUseProgramObjectARB");
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetUniformLocationARB");
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteProgramsARB");
PFNGLDETACHOBJECTARBPROC glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glDetachObjectARB");
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) glXGetProcAddressARB((const GLubyte*) "glDeleteObjectARB");
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC) glXGetProcAddressARB((const GLubyte*) "glValidateProgramARB");
PFNGLUNIFORM4FARBPROC glUniform4fARB = (PFNGLUNIFORM4FARBPROC) glXGetProcAddressARB((const GLubyte*) "glUniform4fARB");
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetProgramivARB");
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glXGetProcAddressARB((const GLubyte*) "glGetProgramInfoLog");
PFNGLGETSHADERIVPROC glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddressARB((const GLubyte*) "glGetShaderiv");
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddressARB((const GLubyte*) "glGetShaderInfoLog");
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetObjectParameterivARB");
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) glXGetProcAddressARB((const GLubyte*) "glGetInfoLogARB");

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
ShaderProgram::ShaderProgram()
	: _program(0), _vertexShader(0), _fragmentShader(0)
{
	_program = glCreateProgramObjectARB();
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderProgram::~ShaderProgram()
{
	if (_program > 0)
		glDeleteProgramsARB(1, &_program);
}

std::string ShaderProgram::readFile(lpcstr filename)
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
 * \param type
 *   Тип создаваемого шейдера.
 * 
 * \param source
 *   Исходный код шейдера.
 */
u32 ShaderProgram::compile(ShaderTypes type, lpcstr source)
{
	u32 shader = glCreateShaderObjectARB(ShaderTypeUtils::toGL(type));
	glShaderSourceARB(shader, 1, &source, NULL);
	glCompileShaderARB(shader);

	if (_checkStatus(shader, GL_OBJECT_COMPILE_STATUS_ARB)) {
		// Empty
	}

	return shader;
}

/*!
 * \brief
 *   Связывает шейдерные объекты с программным объектом.
 * 
 * \param shaders
 *   Дескрипторы связываемых шейдерных объектов.
 */
void ShaderProgram::attach(std::vector<u32> shaders)
{
	for (auto shader : shaders)
		glAttachObjectARB(_program, shader);
}

/*!
 * \brief
 *   Отсоединяет шейдерный объект от программного объекта.
 * 
 * \param shaders
 *   Дескрипторы отвязываемых шейдерных объектов.
 */
void ShaderProgram::detach(std::vector<u32> shaders)
{
	for (auto shader : shaders)
		glDetachObjectARB(_program, shader);

	std::for_each(shaders.begin(), shaders.end(), glDeleteObjectARB);
}

/*!
 * \brief
 *   Компоновка шей­дерных объектов.
 */
void ShaderProgram::link()
{
	glLinkProgramARB(_program);
	if (_checkStatus(_program, GL_OBJECT_LINK_STATUS_ARB)) {
		// Empty
	}
}

/*!
 * \brief
 *   Проверяет программный объект.
 */
void ShaderProgram::validate()
{
	glValidateProgramARB(_program);
	if (_checkStatus(_program, GL_OBJECT_VALIDATE_STATUS_ARB)) {
		// Empty
	}
}

void ShaderProgram::use()
{
	if (_program > 0) {
		glUseProgramObjectARB(_program);

		for (auto iter : _uniformVec4fSets)
			glUniform4fARB(glGetUniformLocationARB(_program, iter.first.c_str()), iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
	}
}

void ShaderProgram::unuse()
{
	if (_program > 0)
		glUseProgramObjectARB(0);
}

void ShaderProgram::setUniformVector4(const std::string &uniform, const math::TVector4<float> &vector4)
{
	_uniformVec4fSets[uniform] = vector4;
}

void ShaderProgram::setUniformColor(const std::string &uniform, const math::TColor<float> &color)
{
	_uniformVec4fSets[uniform] = color.toVec4();
}

s32 ShaderProgram::_checkStatus(u32 shader, u32 name)
{
	int status = 0, length = 0;

	glGetObjectParameterivARB(shader, name, &status);
	if (status == FAILURE_STATUS) {
		glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
		if (length > 1) {
			lpstr info = (lpstr)malloc(length);
			glGetInfoLogARB(shader, length, NULL, info);
			printf("Failed:\n%s", info);
			free(info);
		}
	}

	return status;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)