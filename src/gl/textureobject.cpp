#include "textureobject.h"
#include "texturecreateinfo.h"
#include "textureexception.h"
#include "texturetarget.h"
#include "pixelformat.h"
#include "extensions.h"
#include "typeutils.h"
#include "../utils/stringhelper.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum TextureObject::translateTargetToGLenum(u32 target) {
	switch (target) {
	case kTextureTarget_2D: return GL_TEXTURE_2D;
	case kTextureTarget_2D_Array: return GL_TEXTURE_2D_ARRAY; // GL_VERSION_3_0
	case kTextureTarget_Rectangle: return GL_TEXTURE_RECTANGLE_ARB;
	case kTextureTarget_CubeMap: return GL_TEXTURE_CUBE_MAP;
	default: return INVALID_TYPE;
	}
}

GLenum TextureObject::translatePixelFormatToGLenum(u32 format) {
	switch (format) {
	case kPixelFormat_R: return GL_RED;
	case kPixelFormat_R32F: return GL_R32F;
	case kPixelFormat_RG: return GL_RG;
	case kPixelFormat_RGB: return GL_RGB;
	case kPixelFormat_RGB8: return GL_RGB8;
	case kPixelFormat_RGBA: return GL_RGBA;
	case kPixelFormat_RGBA8: return GL_RGBA8;
	case kPixelFormat_RGBA32F: return GL_RGBA32F;
	case kPixelFormat_HDR: return GL_RGBA32F;
	case kPixelFormat_DEPTH: return GL_DEPTH_COMPONENT24;
	case kPixelFormat_BGR: return GL_BGR;
	case kPixelFormat_BGRA: return GL_BGRA;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
TextureObject::TextureObject() {
	/* Получаем максимальное разрешение текстуры. */
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
TextureObject::~TextureObject() {
	if (glIsTexture(_resourceHandle))
		glDeleteTextures(1, &_resourceHandle);
}

void TextureObject::create(const TextureCreateInfo &createInfo) {
	if (createInfo.size.getW() <= 0 OR createInfo.size.getH() <= 0)
		return;

	GLenum status = glGetError();

	_target = TextureObject::translateTargetToGLenum(createInfo.target);
	_format = TextureObject::translatePixelFormatToGLenum(createInfo.format);
	_internalFormat = TextureObject::translatePixelFormatToGLenum(createInfo.internalFormat);

	glGenTextures(1, &_resourceHandle);
	glBindTexture(_target, _resourceHandle);
	glTexImage2D(_target, createInfo.mipmapLevel, _internalFormat, createInfo.size.getW(), createInfo.size.getH(), 0, _format, TypeUtils::toGL(createInfo.dataType), createInfo.pixels);
	if ((status = glGetError()) != GL_NO_ERROR)
		throw TextureCreationException((lpcstr) gluErrorString(status));

	glBindTexture(_target, 0);
}

/*!
 * \brief
 *   Устанавливает активацию текстурного блока.
 * 
 * \note
 *   Блок GL_TEXTURE0_ARB всегда активирован по-умолчанию.
 *
 * \param[in] channel
 *   Канал текстурного блока.
 */
void TextureObject::setActive(s32 channel) {
	Extensions::glActiveTextureARB(GL_TEXTURE0_ARB + channel);
}

void TextureObject::bind() {
	glEnable(_target);
	glBindTexture(_target, _resourceHandle);
}

void TextureObject::unbind() {
	glBindTexture(_target, 0);
	glDisable(_target);
}

/*!
 * \brief
 *   Получает текстурную цель.
 *
 * \return
 *   Текстурная цель.
 */
u32 TextureObject::getTarget() const {
	switch (_target) {
	case GL_TEXTURE_2D: return kTextureTarget_2D;
	case GL_TEXTURE_2D_ARRAY: return kTextureTarget_2D_Array; // GL_VERSION_3_0
	case GL_TEXTURE_RECTANGLE_ARB: return kTextureTarget_Rectangle;
	case GL_TEXTURE_CUBE_MAP: return kTextureTarget_CubeMap;
	default: return INVALID_TYPE;
	}
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)