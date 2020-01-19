#include "PrecompiledHeaders.h"
#include "InputSystem.h"
#include "..\Imgui\imgui.h"
#include <iostream>

KeyCode InputSystem::StringToKeycode(const char* str)
{
	if (Map_KeyCode.find(str) != Map_KeyCode.end())
		return Map_KeyCode[str];
	return NONE;
}

bool InputSystem::KeyDown(KeyCode key)
{
	return (_currBuffer[key] & 0x80) ? !(_prevBuffer[key] & 0x80)
		: false;
}

bool InputSystem::KeyHold(KeyCode key)
{
	return _currBuffer[key] & 0x80;
}

bool InputSystem::KeyRelease(KeyCode key)
{
	return (!(_currBuffer[key] & 0x80)) ? (_prevBuffer[key] & 0x80)
		: false;
}

void InputSystem::Init()
{
	Map_KeyCode["NONE"] = NONE;
	Map_KeyCode["MOUSE_LBUTTON"] = MOUSE_LBUTTON;
	Map_KeyCode["MOUSE_RBUTTON"] = MOUSE_RBUTTON;
	Map_KeyCode["KEY_CANCEL"] = KEY_CANCEL;
	Map_KeyCode["MOUSE_MBUTTON"] = MOUSE_MBUTTON;
	Map_KeyCode["KEYB_BACKSPACE"] = KEYB_BACKSPACE;
	Map_KeyCode["KEYB_TAB"] = KEYB_TAB;
	Map_KeyCode["KEYB_CLEAR"] = KEYB_CLEAR;
	Map_KeyCode["KEYB_ENTER"] = KEYB_ENTER;
	Map_KeyCode["KEYB_SHIFT"] = KEYB_SHIFT;
	Map_KeyCode["KEYB_CTRL"] = KEYB_CTRL;
	Map_KeyCode["KEYB_ALT"] = KEYB_ALT;
	Map_KeyCode["KEYB_PAUSE	"] = KEYB_PAUSE;
	Map_KeyCode["KEYB_CAPS"] = KEYB_CAPS;
	Map_KeyCode["KEYB_ESCAPE"] = KEYB_ESCAPE;
	Map_KeyCode["KEYB_SPACEBAR"] = KEYB_SPACEBAR;
	Map_KeyCode["KEYB_PAGEUP"] = KEYB_PAGEUP;
	Map_KeyCode["KEYB_PAGEDOWN"] = KEYB_PAGEDOWN;
	Map_KeyCode["KEYB_END"] = KEYB_END;
	Map_KeyCode["KEYB_HOME"] = KEYB_HOME;
	Map_KeyCode["KEYB_LEFT"] = KEYB_LEFT;
	Map_KeyCode["KEYB_UP"] = KEYB_UP;
	Map_KeyCode["KEYB_RIGHT"] = KEYB_RIGHT;
	Map_KeyCode["KEYB_DOWN"] = KEYB_DOWN;
	Map_KeyCode["KEYB_SELECT"] = KEYB_SELECT;
	Map_KeyCode["KEYB_PRINT"] = KEYB_PRINT;
	Map_KeyCode["KEYB_EXECUTE"] = KEYB_EXECUTE;
	Map_KeyCode["KEYB_PRINTSCREEN"] = KEYB_PRINTSCREEN;
	Map_KeyCode["KEYB_INSERT"] = KEYB_INSERT;
	Map_KeyCode["KEYB_DELETE"] = KEYB_DELETE;
	Map_KeyCode["KEYB_HELP"] = KEYB_HELP;
	Map_KeyCode["KEYB_0"] = KEYB_0;
	Map_KeyCode["KEYB_1"] = KEYB_1;
	Map_KeyCode["KEYB_2"] = KEYB_2;
	Map_KeyCode["KEYB_3"] = KEYB_3;
	Map_KeyCode["KEYB_4"] = KEYB_4;
	Map_KeyCode["KEYB_5"] = KEYB_5;
	Map_KeyCode["KEYB_6"] = KEYB_6;
	Map_KeyCode["KEYB_7"] = KEYB_7;
	Map_KeyCode["KEYB_8"] = KEYB_8;
	Map_KeyCode["KEYB_9"] = KEYB_9;
	Map_KeyCode["KEYB_A"] = KEYB_A;
	Map_KeyCode["KEYB_B"] = KEYB_B;
	Map_KeyCode["KEYB_C"] = KEYB_C;
	Map_KeyCode["KEYB_D"] = KEYB_D;
	Map_KeyCode["KEYB_E"] = KEYB_E;
	Map_KeyCode["KEYB_F"] = KEYB_F;
	Map_KeyCode["KEYB_G"] = KEYB_G;
	Map_KeyCode["KEYB_H"] = KEYB_H;
	Map_KeyCode["KEYB_I"] = KEYB_I;
	Map_KeyCode["KEYB_J"] = KEYB_J;
	Map_KeyCode["KEYB_K"] = KEYB_K;
	Map_KeyCode["KEYB_L"] = KEYB_L;
	Map_KeyCode["KEYB_M"] = KEYB_M;
	Map_KeyCode["KEYB_N"] = KEYB_N;
	Map_KeyCode["KEYB_O"] = KEYB_O;
	Map_KeyCode["KEYB_P"] = KEYB_P;
	Map_KeyCode["KEYB_Q"] = KEYB_Q;
	Map_KeyCode["KEYB_R"] = KEYB_R;
	Map_KeyCode["KEYB_S"] = KEYB_S;
	Map_KeyCode["KEYB_T"] = KEYB_T;
	Map_KeyCode["KEYB_U"] = KEYB_U;
	Map_KeyCode["KEYB_V"] = KEYB_V;
	Map_KeyCode["KEYB_W"] = KEYB_W;
	Map_KeyCode["KEYB_X"] = KEYB_X;
	Map_KeyCode["KEYB_Y"] = KEYB_Y;
	Map_KeyCode["KEYB_Z"] = KEYB_Z;
	Map_KeyCode["KEYB_SLEEP	"] = KEYB_SLEEP;
	Map_KeyCode["KEYB_NUMPAD0"] = KEYB_NUMPAD0;
	Map_KeyCode["KEYB_NUMPAD1"] = KEYB_NUMPAD1;
	Map_KeyCode["KEYB_NUMPAD2"] = KEYB_NUMPAD2;
	Map_KeyCode["KEYB_NUMPAD3"] = KEYB_NUMPAD3;
	Map_KeyCode["KEYB_NUMPAD4"] = KEYB_NUMPAD4;
	Map_KeyCode["KEYB_NUMPAD5"] = KEYB_NUMPAD5;
	Map_KeyCode["KEYB_NUMPAD6"] = KEYB_NUMPAD6;
	Map_KeyCode["KEYB_NUMPAD7"] = KEYB_NUMPAD7;
	Map_KeyCode["KEYB_NUMPAD8"] = KEYB_NUMPAD8;
	Map_KeyCode["KEYB_NUMPAD9"] = KEYB_NUMPAD9;
	Map_KeyCode["KEYB_NUMPAD_MULTIPLY"] = KEYB_NUMPAD_MULTIPLY;
	Map_KeyCode["KEYB_NUMPAD_ADD"] = KEYB_NUMPAD_ADD;
	Map_KeyCode["KEYB_NUMPAD_SEPARATOR"] = KEYB_NUMPAD_SEPARATOR;
	Map_KeyCode["KEYB_NUMPAD_SUBTRACT"] = KEYB_NUMPAD_SUBTRACT;
	Map_KeyCode["KEYB_NUMPAD_DECIMAL"] = KEYB_NUMPAD_DECIMAL;
	Map_KeyCode["KEYB_NUMPAD_DIVIDE"] = KEYB_NUMPAD_DIVIDE;
	Map_KeyCode["KEYB_F1"] = KEYB_F1;
	Map_KeyCode["KEYB_F2"] = KEYB_F2;
	Map_KeyCode["KEYB_F3"] = KEYB_F3;
	Map_KeyCode["KEYB_F4"] = KEYB_F4;
	Map_KeyCode["KEYB_F5"] = KEYB_F5;
	Map_KeyCode["KEYB_F6"] = KEYB_F6;
	Map_KeyCode["KEYB_F7"] = KEYB_F7;
	Map_KeyCode["KEYB_F8"] = KEYB_F8;
	Map_KeyCode["KEYB_F9"] = KEYB_F9;
	Map_KeyCode["KEYB_F10"] = KEYB_F10;
	Map_KeyCode["KEYB_F11"] = KEYB_F11;
	Map_KeyCode["KEYB_F12"] = KEYB_F12;
	Map_KeyCode["KEYB_F13"] = KEYB_F13;
	Map_KeyCode["KEYB_F14"] = KEYB_F14;
	Map_KeyCode["KEYB_F15"] = KEYB_F15;
	Map_KeyCode["KEYB_F16"] = KEYB_F16;
	Map_KeyCode["KEYB_F17"] = KEYB_F17;
	Map_KeyCode["KEYB_F18"] = KEYB_F18;
	Map_KeyCode["KEYB_F19"] = KEYB_F19;
	Map_KeyCode["KEYB_F20"] = KEYB_F20;
	Map_KeyCode["KEYB_F21"] = KEYB_F21;
	Map_KeyCode["KEYB_F22"] = KEYB_F22;
	Map_KeyCode["KEYB_F23"] = KEYB_F23;
	Map_KeyCode["KEYB_F24"] = KEYB_F24;
	Map_KeyCode["KEYB_NUMLOCK"] = KEYB_NUMLOCK;
	Map_KeyCode["KEYB_SCROLL_LOCK"] = KEYB_SCROLL_LOCK;
	Map_KeyCode["KEYB_LSHIFT"] = KEYB_LSHIFT;
	Map_KeyCode["KEYB_RSHIFT"] = KEYB_RSHIFT;
	Map_KeyCode["KEYB_LCTRL"] = KEYB_LCTRL;
	Map_KeyCode["KEYB_RCTRL"] = KEYB_RCTRL;
}

void InputSystem::Update(Window& window)
{
	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	int ret = GetKeyboardState(_currBuffer);
	(void)ret;

	GetCursorPos(&_p);
	ScreenToClient(window.Get_hwnd(), &_p);
	//memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	////memset(currBuff, 0, sizeof(unsigned char) * 256);
	////GetKeyState(0);

	////Get current keyboard state
	//GetKeyState(0);
	//int ret = GetKeyboardState(_currBuffer);
	//(void)ret;

	InterruptCheck();
}

Vector3 InputSystem::GetMousePos() const
{
	Vector3 pos{ (float)_p.x - _windowWidth / 2.0f,
	  _windowHeight / 2.0f - (float)_p.y, 1.0f };

	std::cout << pos._x << " : " << pos._y << std::endl;

	return pos;
}

void InputSystem::Exit()
{

}

void InputSystem::SetWindowSize(float width, float height)
{
	_windowWidth = width;
	_windowHeight = height;
}

void InputSystem::InterruptCheck()
{
	if (KeyDown(KEYB_ESCAPE))
	{
		MyFactory.ChangeScene("Quit");
	}

	//bool temp2 = false;
	//if (KeyHold((KeyCode)18) || KeyDown((KeyCode)18))
	//{
	//	temp2 = true;
	//	std::cout << "1" << std::endl;
	//}

	//bool temp = false;
	//if (KeyHold(KEYB_TAB) || KeyDown(KEYB_TAB) || KeyRelease(KEYB_TAB))
	//{
	//	temp = true;
	//	std::cout << "2" << std::endl;
	//}

	//

	//if(temp && temp2)
	//{
	//	exit(0);

	//	MySceneManager.ChangeScene("Quit");
	//}

	//if (KeyHold((KeyCode)18) && KeyHold((KeyCode)17) && KeyHold(KEYB_DELETE))
	//{
	//	MySceneManager.ChangeScene("Quit");
	//}
}