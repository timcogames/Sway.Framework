#include "texturesampler.h"
#include "texturefilter.h"
#include "texturewrap.h"
#include "comparefunc.h"
#include "stencilop.h"
#include "textureobject.h"
#include "extensions.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum TextureSampler::translateWrapToGLenum(u32 wrap) {
	switch (wrap) {
	case kTextureWrap_Repeat: return GL_REPEAT;
	case kTextureWrap_Clamp: return GL_CLAMP_TO_EDGE;
	default: return INVALID_TYPE;
	}
}

GLenum TextureSampler::translateCompareFuncToGLenum(u32 compareFunc) {
	switch (compareFunc) {
	case kCompareFunc_Never: return GL_NEVER;
	case kCompareFunc_Always: return GL_ALWAYS;
	case kCompareFunc_Equal: return GL_EQUAL;
	case kCompareFunc_NotEqual: return GL_NOTEQUAL;
	case kCompareFunc_Less: return GL_LESS;
	case kCompareFunc_LessEqual: return GL_LEQUAL;
	case kCompareFunc_Greater: return GL_GREATER;
	case kCompareFunc_GreaterEqual: return GL_GEQUAL;
	default: return INVALID_TYPE;
	}
}

GLenum TextureSampler::translateStencilOpToGLenum(u32 stencilOp) {
switch (stencilOp) {
	case kStencilOp_Keep: return GL_KEEP;
	case kStencilOp_Replace: return GL_REPLACE;
	case kStencilOp_Increment: return GL_INCR;
	case kStencilOp_IncrementWrap: return GL_INCR_WRAP;
	case kStencilOp_Decrement: return GL_DECR;
	case kStencilOp_DecrementWrap: return GL_DECR_WRAP;
	case kStencilOp_Invert: return GL_INVERT;
	default: return INVALID_TYPE;
	}
}

/*!
 * \brief
 *   Конструктор класса.
 *
 *   Выполняет инициализацию нового экземпляра класса.
 */
TextureSampler::TextureSampler(TextureObject *texture)
	: _texture(texture) {

	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_maxAnisotropy);
}

/*!
 * \brief
 *   Деструктор класса.
 *
 *   Освобождает захваченные ресурсы.
 */
TextureSampler::~TextureSampler() {
	// Empty
}

void TextureSampler::setFilter(u32 filter) {
	GLenum target = TextureObject::translateTargetToGLenum(_texture->getTarget());

	glBindTexture(target, _texture->getHandle());
	
	switch (filter) {
	case kTextureFilter_Nearest:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		break;
	case kTextureFilter_Linear:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		break;
	case kTextureFilter_Trilinear:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		break;
	case kTextureFilter_Anisotropic4x:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
		break;
	case kTextureFilter_Anisotropic8x:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
		break;
	case kTextureFilter_Anisotropic16x:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
		break;
	}

	glBindTexture(target, 0);
}

void TextureSampler::setWrapMode(u32 wrapS, u32 wrapT, u32 wrapR) {
	GLenum target = TextureObject::translateTargetToGLenum(_texture->getTarget());

	glBindTexture(target, _texture->getHandle());

	glTexParameteri(target, GL_TEXTURE_WRAP_S, TextureSampler::translateWrapToGLenum(wrapS));
	glTexParameteri(target, GL_TEXTURE_WRAP_T, TextureSampler::translateWrapToGLenum(wrapT));
	glTexParameteri(target, GL_TEXTURE_WRAP_R, TextureSampler::translateWrapToGLenum(wrapR));

	glBindTexture(target, 0);
}

void TextureSampler::setStencilFunc(u32 stencilFunc, s32 reference, u32 mask) {
	glStencilFunc(TextureSampler::translateCompareFuncToGLenum(stencilFunc), reference, mask);
}

/*!
 * \brief
 *   Получает максимальный уровень анизотропной фильтрации.
 *
 * \return
 *   Уровень анизотропной фильтрации.
 */
s32 TextureSampler::getMaxAnisotropicLevel() const {
	return _maxAnisotropy;
}

NAMESPACE_END(gl)
NAMESPACE_END(sway)