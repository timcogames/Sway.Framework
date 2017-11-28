#ifndef SWAY_GL_SHADEREXCEPTION_H
#define SWAY_GL_SHADEREXCEPTION_H

#include "extensions.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class ShaderUtils {
public:
	static std::string getErrorInfo(ResourceHandle_t handle) {
		int maxLength = 0;
		std::string info;

		Extensions::glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &maxLength);
		if (maxLength > 0) {
			lpstr buf = (lpstr) malloc(maxLength);
			Extensions::glGetInfoLogARB(handle, maxLength, NULL, buf);
			info = std::string(buf);
			free(buf);
		}

		return info;
	}
};

class ShaderCompilationException : public Exception {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderCompilationException(const std::string &message)
		: Exception("Shader source compilation failed.\n", message) {
		// Empty
	}
};

class ShaderLinkageException : public Exception {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderLinkageException(const std::string &message)
		: Exception("Shader linkage failed.\n", message) {
		// Empty
	}
};

class ShaderValidationException : public Exception {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderValidationException(const std::string &message)
		: Exception("Shader validation failed.\n", message) {
		// Empty
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_SHADEREXCEPTION_H