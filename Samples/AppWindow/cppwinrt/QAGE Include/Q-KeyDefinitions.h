/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

		Keyboard Definitions - (Aged)

*/

#ifndef KEYDEFINITIONS_H
#define KEYDEFINITIONS_H

namespace GVARS
{

#if 0
#define SDL_KEY_STATES 0
#endif

#ifdef SDL_KEY_STATES
inline bool KEY_PRESS_DOWN(int SDL_code)
	{
	QInt *keystate = SDL_GetKeyState(NULL);
	if ( keystate[SDL_code] ) return true;
	else return false;
	}

inline bool KEY_UP(int SDL_code)
	{
	QInt *keystate = SDL_GetKeyState(NULL);
	if ( keystate[SDL_code] ) return false;
	else return true;
	}
#else
// these read the keyboard asynchronously
#if defined(WIN32)
#if DEKEY
#define KEY_PRESS_DOWN(QIN_code) ((GetAsyncKeyState(QIN_code) & 0x8000) ? 1 : 0)
#define KEY_UP(QIN_code)   ((GetAsyncKeyState(QIN_code) & 0x8000) ? 0 : 1)
#else
extern int KEY_PRESS_DOWN(int QIN_code);
extern int KEY_DOWN_LOCK(int QIN_code);
extern int KEY_UP(int QIN_code);
extern int KEY_DOWN_w(void);
extern int KEY_DOWN_s(void);
extern int KEY_DOWN_a(void);
extern int KEY_DOWN_d(void);
extern int KEY_DOWN_PK(int QIN_code);
extern int KEY_UP_PK(int QIN_code);
extern int KEY_DOWN_PK_w(void);
extern int KEY_DOWN_PK_s(void);
extern int KEY_DOWN_PK_a(void);
extern int KEY_DOWN_PK_d(void);
extern int KEY_DOWN_PC_w(void);
extern int KEY_DOWN_PC_s(void);
extern int KEY_DOWN_PC_a(void);
extern int KEY_DOWN_PC_d(void);
extern int KEY_DOWN_PCX_w(void);
extern int KEY_DOWN_PCX_s(void);
extern int KEY_DOWN_PCX_a(void);
extern int KEY_DOWN_PCX_d(void);
#endif
#else
#define KEY_PRESS_DOWN(QIN_code) false
#define KEY_UP(QIN_code) false
#endif
#endif

#ifndef SDL_KEY_STATES 

#define QIN_a 0x41
#define QIN_b 0x42
#define QIN_c 0x43
#define QIN_d 0x44
#define QIN_e 0x45
#define QIN_f 0x46
#define QIN_g 0x47
#define QIN_h 0x48
#define QIN_i 0x49
#define QIN_j 0x4A
#define QIN_k 0x4B
#define QIN_l 0x4C
#define QIN_m 0x4D
#define QIN_n 0x4E
#define QIN_o 0x4F
#define QIN_p 0x50
#define QIN_q 0x51
#define QIN_r 0x52
#define QIN_s 0x53
#define QIN_t 0x54
#define QIN_u 0x55
#define QIN_v 0x56
#define QIN_w 0x57
#define QIN_x 0x58
#define QIN_y 0x59
#define QIN_z 0x5A

#define QIN_0 0x30
#define QIN_1 0x31
#define QIN_2 0x32
#define QIN_3 0x33
#define QIN_4 0x34
#define QIN_5 0x35
#define QIN_6 0x36
#define QIN_7 0x37
#define QIN_8 0x38
#define QIN_9 0x39

#define QIN_KP0 0x60
#define QIN_KP1 0x61
#define QIN_KP2 0x62
#define QIN_KP3 0x63
#define QIN_KP4 0x64
#define QIN_KP5 0x65
#define QIN_KP6 0x66
#define QIN_KP7 0x67
#define QIN_KP8 0x68
#define QIN_KP9 0x69
#define QIN_ASTERISK 0x6A
#define QIN_PLUS 0x6B
#define QIN_SEPARATOR 0x6C
#define QIN_MINUS 0x6D
#define QIN_DECIMAL 0x6E
#define QIN_DIVIDE 0x6F
#define QIN_F1 0x70
#define QIN_F2 0x71
#define QIN_F3 0x72
#define QIN_F4 0x73
#define QIN_F5 0x74
#define QIN_F6 0x75
#define QIN_F7 0x76
#define QIN_F8 0x77
#define QIN_F9 0x78
#define QIN_F10 0x79
#define QIN_F11 0x7A
#define QIN_F12 0x7B
#define QIN_F13 0x7C
#define QIN_F14 0x7D
#define QIN_F15 0x7E
#define QIN_F16 0x7F
#define QIN_F17 0x80
#define QIN_F18 0x81
#define QIN_F19 0x82
#define QIN_F20 0x83
#define QIN_F21 0x84
#define QIN_F22 0x85
#define QIN_F23 0x86
#define QIN_F24 0x87

#define QIN_NUMLOCK 0x90
#define QIN_SCROLLOCK 0x91

#define QIN_LSHIFT 0xA0
#define QIN_RSHIFT 0xA1
#define QIN_LCONTROL 0xA2
#define QIN_RCONTROL 0xA3
#define QIN_LMENU 0xA4
#define QIN_RMENU 0xA5

#define QIN_ESCAPE 0x1B
#define QIN_SPACE 0x20
#define QIN_PAGEUP 0x21 //PRIOR
#define QIN_PAGEDOWN 0x22 //NEXT
#define QIN_END 0x23
#define QIN_HOME 0x24
#define QIN_LEFT 0x25
#define QIN_UP 0x26
#define QIN_RIGHT 0x27
#define QIN_DOWN 0x28
#define QIN_SELECT 0x29
#define QIN_PRINT 0x2A
#define QIN_EXECUTE 0x2B
#define QIN_SNAPSHOT 0x2C
#define QIN_INSERT 0x2D
#define QIN_DELETE 0x2E
#define QIN_HELP 0x2F

#define QIN_LBUTTON 0x01
#define QIN_RBUTTON 0x02
#define QIN_CANCEL 0x03
#define QIN_MBUTTON 0x04    /* NOT contiguous with L & RBUTTON */

#define QIN_BACK 0x08
#define QIN_TAB 0x09
#define QIN_CLEAR 0x0C
#define QIN_RETURN 0x0D

#define QIN_SHIFT 0x10
#define QIN_CONTROL 0x11
#define QIN_MENU 0x12
#define QIN_PAUSE 0x13
#define QIN_CAPSLOCK 0x14
#endif

};

#pragma message ("###  Key Definitions  [Q-KeyDefinitions.h]")

#endif