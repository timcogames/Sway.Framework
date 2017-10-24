#ifndef SWAY_GL_DATATYPEINFO_H
#define SWAY_GL_DATATYPEINFO_H

#include "../defines.h"
#include "../types.h"

#include <GL/gl.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

class DataTypeInfo {
public:
	/**
	 * Определяет поддерживаемые форматы индексов.
	 */
	enum IndexFormats {
		kIndexFormat_INDEX8  = GL_UNSIGNED_BYTE,
		kIndexFormat_INDEX16 = GL_UNSIGNED_SHORT,
		kIndexFormat_INDEX32 = GL_UNSIGNED_INT
	};

	enum Types {
		kType_Int    = 0xB5BE,
		kType_Float  = 0xA411,
		kType_Float2 = 0x0D55,
		kType_Float3 = 0xDAB1,
		kType_Float4 = 0x49B9,
		kType_Double = 0xCB72,
		kType_Short  = 0x3F0D,
		kType_Byte   = 0x6F34,
		kType_UInt   = 0x329A,
		kType_UInt16 = 0x79DE,
		kType_UByte  = 0x5B69
	};

	static u32 getComponentCount(u32 type) {
		switch (type) {
		case kType_Float2: return 2;
		case kType_Float3: return 3;
		case kType_Float4: return 4;
		case kType_Int:
		case kType_Float:
		case kType_Double:
		case kType_Short:
		case kType_Byte:
		case kType_UInt:
		case kType_UInt16:
		case kType_UByte:
			return 1;
		default:
			return 0;
		};
	}

	static u32 getElementSize(u32 type) {
		switch (type) {
		case kType_Float2: return sizeof(f32) * 2;
		case kType_Float3: return sizeof(f32) * 3;
		case kType_Float4: return sizeof(f32) * 4;
		case kType_Int:    return sizeof(s32);
		case kType_Float:  return sizeof(f32);
		case kType_Double: return sizeof(f64);
		case kType_Short:  return sizeof(s16);
		case kType_Byte:   return sizeof(lpstr);
		case kType_UInt:   return sizeof(u32);
		case kType_UInt16: return sizeof(u16);
		case kType_UByte:  return sizeof(u8);
		default:
			return 0;
		};
	}

	static u32 toGL(u32 type) {
		switch (type) {
		case kType_Int:    return GL_INT;
		case kType_Float:  return GL_FLOAT;
		case kType_Double: return GL_DOUBLE;
		case kType_Short:  return GL_SHORT;
		case kType_Byte:   return GL_BYTE;
		/* Поддерживаемые форматы индексов. */
		case kType_UInt:   return GL_UNSIGNED_INT;
		case kType_UInt16: return GL_UNSIGNED_SHORT;
		case kType_UByte:  return GL_UNSIGNED_BYTE;
		default:
			return INVALID_TYPE;
		}
	}
};

NAMESPACE_END(gl)
NAMESPACE_END(sway)

#endif // SWAY_GL_DATATYPEINFO_H