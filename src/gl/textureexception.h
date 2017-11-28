#ifndef SWAY_GL_TEXTUREEXCEPTION_H
#define SWAY_GL_TEXTUREEXCEPTION_H

#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class TextureCreationException : public Exception {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	TextureCreationException(const std::string &message)
		: Exception("Texture creation failed.\n", message) {
		// Empty
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTUREEXCEPTION_H