#ifndef SWAY_GL_SHADEREXCEPTION_H
#define SWAY_GL_SHADEREXCEPTION_H

#include "extensions.h"
#include "glprereqs.h"

#include <boost/make_unique.hpp> // boost::make_unique

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class ShaderUtils {
public:
	static std::string getErrorInfo(ResourceHandle_t handle) {
		std::string result;
		GLint logLength;
		
		Extensions::glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
		if (logLength > 0) {
			const auto logInfo = boost::make_unique<GLchar[]>(logLength);
			Extensions::glGetInfoLogARB(handle, logLength, NULL, logInfo.get());

			result = std::string(logInfo.get());
		}

		return result;
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