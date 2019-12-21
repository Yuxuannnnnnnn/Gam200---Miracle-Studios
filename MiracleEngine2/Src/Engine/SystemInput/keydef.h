#pragma once

#ifndef KEYDEF_H
#define KEYDEF_H

/*
* Virtual Keys, Standard Set
*/
#define MOUSE_LBUTTON        0x01 /mouse left button/
#define MOUSE_RBUTTON        0x02 /mouse right button/
#define KEY_CANCEL           0x03 /Control-break processing, CTRL+Break button/
#define MOUSE_MBUTTON        0x04 /* NOT contiguous with L & RBUTTON, mouse middle button */

/* not using
* 0x05 : Windows 2000: X1 mouse button
* 0x06 : Windows 2000: X2 mouse button
* 0x07 : unassigned
*/

#define KEYB_BACKSPACE        0x08
#define KEYB_TAB              0x09

/* not using
* 0x0A - 0x0B : reserved
*/

#define KEYB_CLEAR            0x0C
#define KEYB_ENTER            0x0D

#define KEYB_SHIFT            0x10
#define KEYB_CTRL		      0x11
#define KEYB_ALT              0x12
#define KEYB_PAUSE            0x13
#define KEYB_CAPS             0x14

/* not using
* 0x15 : IME Kana mode
* 0x15 : IME Hanguel mode(maintained for compatibility; use VK_HANGUL)
* 0x15 : IME Hangul mode
* 0x16 : undefined
* 0x17 : IME Junja mode
* 0x18 : IME final mode
* 0x19 : IME Hanja mode
* 0x19 : IME Kanji mode
* 0x1A : undefined
*/

#define KEYB_ESCAPE			 0x1B

/* not using
* 0x1C : IME convert
* 0x1D : IME nonconvert
* 0x1E : IME accept
* 0x1F : IME mode change request
*/

#define KEYB_SPACEBAR         0x20
#define KEYB_PAGEUP           0x21
#define KEYB_PAGEDOWN         0x22
#define KEYB_END			  0x23
#define KEYB_HOME             0x24
#define KEYB_LEFT             0x25
#define KEYB_UP               0x26
#define KEYB_RIGHT            0x27
#define KEYB_DOWN             0x28
#define KEYB_SELECT           0x29
#define KEYB_PRINT            0x2A
#define KEYB_EXECUTE          0x2B
#define KEYB_PRINTSCREEN      0x2C
#define KEYB_INSERT           0x2D
#define KEYB_DELETE           0x2E
#define KEYB_HELP			  0x2F

#define KEYB_0				 0x30
#define KEYB_1				 0x31
#define KEYB_2				 0x32
#define KEYB_3				 0x33
#define KEYB_4				 0x34
#define KEYB_5				 0x35
#define KEYB_6				 0x36
#define KEYB_7				 0x37
#define KEYB_8				 0x38
#define KEYB_9				 0x39

/* not using
* 0x40 : unassigned
*/

#define KEYB_A				 0x41
#define KEYB_B				 0x42
#define KEYB_C				 0x43
#define KEYB_D				 0x44
#define KEYB_E				 0x45
#define KEYB_F				 0x46
#define KEYB_G				 0x47
#define KEYB_H				 0x48
#define KEYB_I				 0x49
#define KEYB_J				 0x4A
#define KEYB_K				 0x4B
#define KEYB_L				 0x4C
#define KEYB_M				 0x4D
#define KEYB_N				 0x4E
#define KEYB_O				 0x4F
#define KEYB_P				 0x50
#define KEYB_Q				 0x51
#define KEYB_R				 0x52
#define KEYB_S				 0x53
#define KEYB_T				 0x54
#define KEYB_U				 0x55
#define KEYB_V				 0x56
#define KEYB_W				 0x57
#define KEYB_X				 0x58
#define KEYB_Y				 0x59
#define KEYB_Z				 0x5A

/*
* 0x5B : Left Windows key(Microsoft Natural Keyboard)
* 0x5C : Right Windows key(Microsoft Natural Keyboard)
* 0x5D : Applications key(Microsoft Natural Keyboard)
* 0x5E : reserved
*/

#define KEYB_SLEEP            0x5F
#define KEYB_NUMPAD0		  0x60
#define KEYB_NUMPAD1          0x61
#define KEYB_NUMPAD2          0x62
#define KEYB_NUMPAD3          0x63
#define KEYB_NUMPAD4          0x64
#define KEYB_NUMPAD5          0x65
#define KEYB_NUMPAD6          0x66
#define KEYB_NUMPAD7          0x67
#define KEYB_NUMPAD8          0x68
#define KEYB_NUMPAD9          0x69
#define KEYB_NUMPAD_MULTIPLY  0x6A
#define KEYB_NUMPAD_ADD       0x6B
#define KEYB_NUMPAD_SEPARATOR 0x6C
#define KEYB_NUMPAD_SUBTRACT  0x6D
#define KEYB_NUMPAD_DECIMAL   0x6E
#define KEYB_NUMPAD_DIVIDE    0x6F
#define KEYB_F1               0x70
#define KEYB_F2               0x71
#define KEYB_F3               0x72
#define KEYB_F4               0x73
#define KEYB_F5               0x74
#define KEYB_F6               0x75
#define KEYB_F7               0x76
#define KEYB_F8               0x77
#define KEYB_F9               0x78
#define KEYB_F10              0x79
#define KEYB_F11              0x7A
#define KEYB_F12              0x7B
#define KEYB_F13              0x7C
#define KEYB_F14              0x7D
#define KEYB_F15              0x7E
#define KEYB_F16              0x7F
#define KEYB_F17              0x80
#define KEYB_F18              0x81
#define KEYB_F19              0x82
#define KEYB_F20              0x83
#define KEYB_F21              0x84
#define KEYB_F22              0x85
#define KEYB_F23              0x86
#define KEYB_F24              0x87

/* not using
* 0x88 - 0x8F : unassigned
*/

#define KEYB_NUMLOCK          0x90
#define KEYB_SCROLL_LOCK      0x91

/* not using
* 0x92 : '=' key on numpad
* 0x93 - 0x96 : OEM specific
* 0x97 - 0x9F : unassigned
*/

/*
* VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
* Used only as parameters to GetAsyncKeyState() and GetKeyState().
* No other API or message will distinguish left and right keys in this way.
*/
#define KEYB_LSHIFT           0xA0
#define KEYB_RSHIFT           0xA1
#define KEYB_LCTRL            0xA2
#define KEYB_RCTRL            0xA3
#define KEYB_LMENU            0xA4
#define KEYB_RMENU            0xA5

/*
#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC
*/
#define KEYB_VOLUME_MUTE         0xAD
#define KEYB_VOLUME_DOWN         0xAE
#define KEYB_VOLUME_UP           0xAF
#define KEYB_MEDIA_NEXT_TRACK    0xB0
#define KEYB_MEDIA_PREV_TRACK    0xB1
#define KEYB_MEDIA_STOP          0xB2
#define KEYB_MEDIA_PLAY_PAUSE    0xB3
/*
#define KEYB_LAUNCH_MAIL         0xB4
#define KEYB_LAUNCH_MEDIA_SELECT 0xB5

#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7
* 0xB8 - 0xB9 : reserved
*/

#define KEYB_BESIDE_L         0xBA   // ';:' for US
#define KEYB_PLUS			 0xBB   // '+' any country
#define KEYB_COMMA			 0xBC   // ',' any country
#define KEYB_MINUS			 0xBD   // '-' any country
#define KEYB_PERIOD			 0xBE   // '.' any country
#define KEYB_QUESTIONMARK     0xBF   // '/?' for US
#define KEYB_BESIDE_1         0xC0   // '`~' for US

/* not using
* 0xC1 - 0xD7 : reserved
* 0xD8 - 0xDA : unassigned
*/

#define KEYB_SUBSCRIPT_LEFT   0xDB  /*  '[{' for US*/
#define KEYB_OR				 0xDC  /*  '\|' for US*/
#define KEYB_SUBSCRIPT_RIGHT  0xDD  /*  ']}' for US*/
#define KEYB_DOUBLE_QUOTE     0xDE  /*  ''"' for US*/


#endif

