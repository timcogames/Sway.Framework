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


class Exception : public std::exception {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Exception(const std::string &error, const std::string &message)
		: _error(error)
		, _message(message) {
		// Empty
	}

	virtual ~Exception() throw() {
		// Empty
	}
	
	virtual lpcstr what() const throw() {
		return _error.c_str();
	}

	lpcstr message() const {
		return _message.c_str();
	}
	
private:
	std::string _error;
	std::string _message;
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