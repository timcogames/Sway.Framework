#include "shaderprogram.h"
#include "shadertypeutils.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
ShaderProgram::ShaderProgram()
	: _program(0), _vertexShader(0), _fragmentShader(0)
{
	// Empty
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderProgram::~ShaderProgram()
{
	// Empty
}

std::string ShaderProgram::readFile(lpcstr filename)
{
	std::ifstream fileStream(filename, std::ios::binary);
	if (NOT fileStream.is_open())
	{
		printf("File %s not found\n", filename);
		return "";
	}

	std::string fileContent((std::istreambuf_iterator<s8>(fileStream)), std::istreambuf_iterator<s8>());
	fileStream.close();

	return fileContent;
}

/*!
 * \brief
 *   Создает шейдерную программу.
 */
void ShaderProgram::create()
{
	_program = glCreateProgramObjectARB();
}

void ShaderProgram::destroy()
{	
	if (_program > 0)
		glDeleteProgramsARB(1, &_program);
}

u32 ShaderProgram::compile(ShaderTypes type, std::string shaderStr)
{
	u32 shader = glCreateShaderObjectARB(ShaderTypeUtils::toGL(type));
	if (shader == 0)
		std::cerr << "Error compiling shader type: " << ShaderTypeUtils::toStr(type) << std::endl;

	glShaderSourceARB(shader, 1, (const GLcharARB**)shaderStr.c_str(), NULL);
	glCompileShaderARB(shader);

	return shader;
}

void ShaderProgram::attach(std::vector<u32> shaders)
{
	for (auto shader : shaders)
		glAttachObjectARB(_program, shader);
}

void ShaderProgram::detach(std::vector<u32> shaders)
{
	for (auto shader : shaders)
		glDetachObjectARB(_program, shader);

	std::for_each(shaders.begin(), shaders.end(), glDeleteObjectARB);
}

void ShaderProgram::link()
{
	glLinkProgramARB(_program);
}

void ShaderProgram::validate()
{
	glValidateProgramARB(_program);
}

void ShaderProgram::use()
{
	if (_program > 0)
	{
		glUseProgramObjectARB(_program);

		for (auto iter : _uniformVec4fSets)
			glUniform4fARB(glGetUniformLocationARB(_programId, iter.first.c_str()), iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
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

void ShaderProgram::_printProgramLog()
{
	int result = FAILURE_STATUS, logLength = 0;

	glGetProgramiv(_program, GL_LINK_STATUS, &result);
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		lpstr infoLog = new s8[logLength + 1];
		glGetProgramInfoLog(_program, logLength, NULL, infoLog);
		printf("program log: %s\n", infoLog);
	}
}

void ShaderProgram::_printShaderLog(u32 shader)
{
	int result = FAILURE_STATUS, logLength = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		lpstr infoLog = new s8[logLength + 1];
		glGetShaderInfoLog(shader, logLength, NULL, infoLog);
		printf("shader log: %s\n", infoLog);
	}
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)