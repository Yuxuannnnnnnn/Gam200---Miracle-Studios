#include "PrecompiledHeaders.h"
#include "InputSystem.h"
#include "..\Imgui\imgui.h"
#include <iostream>

bool InputSystem::KeyDown(KeyCode key)
{
	return _currBuffer[key] & 0x80;
}

void InputSystem::Init()
{

}

void InputSystem::Update(WindowsSystem& window)
{

	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	int ret = GetKeyboardState(_currBuffer);
	(void)ret;
	GetCursorPos(&_p);

	//ScreenToClient(window.Get_hwnd(), &_p);
}

POINT InputSystem::GetMousePos() const
{
	POINT newP{_p.x - 400 , 300 - _p.y };

	return newP;
}

void InputSystem::Exit()
{

}