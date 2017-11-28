#ifndef SWAY_GL_EXCEPTION_H
#define SWAY_GL_EXCEPTION_H

#include "defines.h"
#include "types.h"

#include <string> // std::string
#include <exception> // std::exception

NAMESPACE_BEGIN(sway)

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

NAMESPACE_END(sway)

#endif // SWAY_GL_EXCEPTION_H