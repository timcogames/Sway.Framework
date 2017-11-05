#ifndef SWAY_TYPES_H
#define SWAY_TYPES_H

namespace sway {
	// signed
	typedef char s8;
	typedef short s16;
	typedef int s32;
	typedef float f32;
	typedef long s64;
	typedef double f64;

	// unsigned
	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long u64;

	// simplified
	typedef s8 *lpstr;
	typedef const s8 *lpcstr;

	enum {
		kType_Char   = 0xB5BE,
		kType_Short  = 0xA411,
		kType_Int    = 0x0D55,
		kType_Float  = 0xDAB1,
		kType_Long   = 0x49B9,
		kType_Double = 0xCB72,
		kType_UChar  = 0x3F0D,
		kType_UShort = 0x6F34,
		kType_UInt   = 0x329A,
		kType_ULong  = 0x79DE
	};

	enum {
		kType_Float2 = 0xE630,
		kType_Float3 = 0x0EB0,
		kType_Float4 = 0xC94B
	};

	class TypeInfo {
	public:
		static u32 getComponentCount(u32 type) {
			switch (type) {
			case kType_Char:
			case kType_Short:
			case kType_Int:
			case kType_Float:
			case kType_Long:
			case kType_Double:
			case kType_UChar:
			case kType_UShort:
			case kType_UInt:
			case kType_ULong:
				return 1;
			case kType_Float2: return 2;
			case kType_Float3: return 3;
			case kType_Float4: return 4;
			default:
				return 0;
			};
		}

		static u32 getElementSize(u32 type) {
			switch (type) {
			case kType_Char:   return sizeof(s8);
			case kType_Short:  return sizeof(s16);
			case kType_Int:    return sizeof(s32);
			case kType_Float:  return sizeof(f32);
			case kType_Long:   return sizeof(s64);
			case kType_Double: return sizeof(f64);
			case kType_UChar:  return sizeof(u8);
			case kType_UShort: return sizeof(u16);
			case kType_UInt:   return sizeof(u32);
			case kType_ULong:  return sizeof(u64);

			case kType_Float2: return sizeof(f32) * 2;
			case kType_Float3: return sizeof(f32) * 3;
			case kType_Float4: return sizeof(f32) * 4;
			default:
				return 0;
			};
		}
	};
}

#endif // SWAY_TYPES_H