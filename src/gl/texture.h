#ifndef SWAY_GL_TEXTURE_H
#define SWAY_GL_TEXTURE_H

#include "resource.h"
#include "texturecreateinfo.h"
#include "glprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class Texture : public Resource {
public:
	static GLenum getGLTarget(u32 target);

	static GLenum getGLPixelFormat(u32 format);

	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Texture();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	virtual ~Texture();

	void create(const TextureCreateInfo &createInfo);

	void bind();

	void unbind();

	void setActive(s32 slot);

private:
	u32 _target;
	u32 _format;
	u32 _internalFormat;
	
	bool _mipmapped;
	bool _compressed;

	s32 _maxTextureSize;
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_TEXTURE_H