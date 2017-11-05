#include "shaderobject.h"
#include "extensions.h"
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum ShaderObject::getGLType(u32 type) {
	switch (type) {
	case kShaderType_Vertex: return GL_VERTEX_SHADER_ARB;
	case kShaderType_Fragment: return GL_FRAGMENT_SHADER_ARB;
	default: return INVALID_TYPE;
	}
}

ShaderObject *ShaderObject::create(const ShaderObjectCreateInfo &createInfo) {
	std::ostringstream preprocessedSource;
	createInfo.preprocessor->evaluate(preprocessedSource);

	std::string dataSource = preprocessedSource.str() + createInfo.source;
	
	ShaderObject *instance = new ShaderObject(createInfo.type);
	instance->compile(dataSource.c_str());
	if (instance->isCompiled()) return instance;

	SAFE_DELETE(instance);
	return 0;
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 * 
 * \param[in] type
 *   Тип создаваемого шейдера.
 */
ShaderObject::ShaderObject(const u32 type)
	: _type(type)
	, _compiled(false) {
		
	_resourceHandle = Extensions::glCreateShaderObjectARB(getGLType(_type));
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
ShaderObject::~ShaderObject() {
	Extensions::glDeleteObjectARB(_resourceHandle);
}

/*!
 * \brief
 *   Выполняет компиляцию шейдерного объекта.
 * 
 * \param[in] source
 *   Исходный код шейдера.
 * 
 * \return
 *   Если компиляция прошла успешно 'true', иначе 'false'.
 */
void ShaderObject::compile(lpcstr source) {
	Extensions::glShaderSourceARB(_resourceHandle, 1, &source, NULL);
	Extensions::glCompileShaderARB(_resourceHandle);

	_compiled = _checkStatus(_resourceHandle, GL_OBJECT_COMPILE_STATUS_ARB);
	if (_compiled) {
		// Empty
	}
}

/*!
 * \brief
 *   Возвращает статус компиляции.
 * 
 * \return
 *   Если компиляция прошла успешно 'true', иначе 'false'.
 */
bool ShaderObject::isCompiled() const {
	return _compiled;
}

/*!
 * brief
 *   Получает тип шейдерного объекта.
 */
u32 ShaderObject::getType() const {
	return _type;
}

//glGetShaderivARB
//glGetShaderInfoLogARB
bool ShaderObject::_checkStatus(ResourceHandle_t shader, u32 name) {
	int status = 0, length = 0;

	Extensions::glGetObjectParameterivARB(shader, name, &status);
	if (NOT status) {
		Extensions::glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
		if (length > 1) {
			lpstr info = (lpstr) malloc(length);
			Extensions::glGetInfoLogARB(shader, length, NULL, info);
			std::cerr << "Failed:\n" << info << std::endl;
			free(info);
		}

		return false;
	}

	return true;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)