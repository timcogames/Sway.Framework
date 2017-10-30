#ifndef SWAY_PLATFORM_UNIX_OIS_KEYCODES_H
#define SWAY_PLATFORM_UNIX_OIS_KEYCODES_H

#include "oisprereqs.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ois)

enum KeyCodes {
	kKeyCode_Unknown = 0,

	kKeyCode_0 = 48,
	kKeyCode_1 = 49,
	kKeyCode_2 = 50,
	kKeyCode_3 = 51,
	kKeyCode_4 = 52,
	kKeyCode_5 = 53,
	kKeyCode_6 = 54,
	kKeyCode_7 = 55,
	kKeyCode_8 = 56,
	kKeyCode_9 = 57,

	kKeyCode_A = 65,
	kKeyCode_B = 66,
	kKeyCode_C = 67,
	kKeyCode_D = 68,
	kKeyCode_E = 69,
	kKeyCode_F = 70,
	kKeyCode_G = 71,
	kKeyCode_H = 72,
	kKeyCode_I = 73,
	kKeyCode_J = 74,
	kKeyCode_K = 75,
	kKeyCode_L = 76,
	kKeyCode_M = 77,
	kKeyCode_N = 78,
	kKeyCode_O = 79,
	kKeyCode_P = 80,
	kKeyCode_Q = 81,
	kKeyCode_R = 82,
	kKeyCode_S = 83,
	kKeyCode_T = 84,
	kKeyCode_U = 85,
	kKeyCode_V = 86,
	kKeyCode_W = 87,
	kKeyCode_X = 88,
	kKeyCode_Y = 89,
	kKeyCode_Z = 90,

	kKeyCode_F1 = 112,
	kKeyCode_F2 = 113,
	kKeyCode_F3 = 114,
	kKeyCode_F4 = 115,
	kKeyCode_F5 = 116,
	kKeyCode_F6 = 117,
	kKeyCode_F7 = 118,
	kKeyCode_F8 = 119,
	kKeyCode_F9 = 120,
	kKeyCode_F10 = 121,
	kKeyCode_F11 = 122,
	kKeyCode_F12 = 123,

	kKeyCode_Backspace = 8,
	kKeyCode_Tab = 9,
	kKeyCode_Enter = 13,
	kKeyCode_CapsLock = 20,
	kKeyCode_Escape = 27,
	kKeyCode_Space = 32,
	kKeyCode_App = 93,
	kKeyCode_Semicolon = 186,
	kKeyCode_Add = 187,
	kKeyCode_Comma = 188,
	kKeyCode_Subtract = 189,
	kKeyCode_Period = 190,
	kKeyCode_Slash = 191,
	kKeyCode_Tilde = 192,
	kKeyCode_LeftBracket = 219,
	kKeyCode_Backslash = 220,
	kKeyCode_RightBracket = 221,
	kKeyCode_Apostrophe = 222,

	kKeyCode_Shift = 16,
	kKeyCode_Ctrl = 17,
	kKeyCode_LeftWin = 91,
	kKeyCode_RightWin = 92,
	kKeyCode_LeftAlt = 164,
	kKeyCode_RightAlt = 165,

	kKeyCode_Insert = 45,
	kKeyCode_Delete = 46,
	kKeyCode_Home = 36,
	kKeyCode_End = 35,
	kKeyCode_PageUp = 33,
	kKeyCode_PageDown = 34,

	kKeyCode_Up = 38,
	kKeyCode_Down = 40,
	kKeyCode_Right = 39,
	kKeyCode_Left = 37,

	kKeyCode_NumLock = 144,
	kKeyCode_NumPad_Divide = 111,
	kKeyCode_NumPad_Multiply = 106,
	kKeyCode_NumPad_Subtract = 109,
	kKeyCode_NumPad_Add = 107,
	kKeyCode_NumPad_Decimal = 110,
	kKeyCode_NumPad_0 = 96,
	kKeyCode_NumPad_1 = 97,
	kKeyCode_NumPad_2 = 98,
	kKeyCode_NumPad_3 = 99,
	kKeyCode_NumPad_4 = 100,
	kKeyCode_NumPad_5 = 101,
	kKeyCode_NumPad_6 = 102,
	kKeyCode_NumPad_7 = 103,
	kKeyCode_NumPad_8 = 104,
	kKeyCode_NumPad_9 = 105
};

NAMESPACE_END(ois)
NAMESPACE_END(sway)

#endif // SWAY_PLATFORM_UNIX_OIS_KEYCODES_H