#include "texture.h"
#include "texturetargets.h"
#include "pixelformats.h"
#include "extensions.h"
#include "typeutils.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum Texture::getGLTarget(u32 target) {
	switch (target) {
	case kTextureTarget_2D:        return GL_TEXTURE_2D;
	case kTextureTarget_2D_Array:  return GL_TEXTURE_2D_ARRAY; // GL_VERSION_3_0
	case kTextureTarget_Rectangle: return GL_TEXTURE_RECTANGLE_ARB;
	case kTextureTarget_CubeMap:   return GL_TEXTURE_CUBE_MAP;
	default: return INVALID_TYPE;
	}
}

GLenum Texture::getGLPixelFormat(u32 format) {
	switch (format) {
	case kPixelFormat_R:       return GL_RED;
	case kPixelFormat_R32F:    return GL_R32F;
	case kPixelFormat_RG:      return GL_RG;
	case kPixelFormat_RGB:     return GL_RGB;
	case kPixelFormat_RGB8:    return GL_RGB8;
	case kPixelFormat_RGBA:    return GL_RGBA;
	case kPixelFormat_RGBA8:   return GL_RGBA8;
	case kPixelFormat_RGBA32F: return GL_RGBA32F;
	case kPixelFormat_HDR:     return GL_RGBA32F;
	case kPixelFormat_DEPTH:   return GL_DEPTH_COMPONENT24;
	case kPixelFormat_BGR:     return GL_BGR;
	case kPixelFormat_BGRA:    return GL_BGRA;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
Texture::Texture()
	: _mipmapped(false)
	, _compressed(false) {

	/* Получаем максимальное разрешение текстуры. */
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
Texture::~Texture() {
	if (glIsTexture(_resourceHandle))
		glDeleteTextures(1, &_resourceHandle);
}

void Texture::create(const TextureCreateInfo &createInfo) {
	if (createInfo.width <= 0 OR createInfo.height <= 0)
		return;

	_target = Texture::getGLTarget(createInfo.target);
	_format = Texture::getGLPixelFormat(createInfo.format);
	_internalFormat = Texture::getGLPixelFormat(createInfo.internalFormat);

	glGenTextures(1, &_resourceHandle);
	glBindTexture(_target, _resourceHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(_target, createInfo.mipLevels, _internalFormat, createInfo.width, createInfo.height, 0, _format, TypeUtils::toGL(createInfo.dataType), createInfo.pixels);
}

void Texture::bind() {
	glEnable(_target);
	glBindTexture(_target, _resourceHandle);
}

void Texture::unbind() {
	glBindTexture(_target, 0);
	glDisable(_target);
}

void Texture::setActive(s32 slot) {
	Extensions::glActiveTextureARB(GL_TEXTURE0_ARB + slot);
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)