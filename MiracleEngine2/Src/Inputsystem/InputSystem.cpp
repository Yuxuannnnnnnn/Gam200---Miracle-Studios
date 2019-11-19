#include "PrecompiledHeaders.h"
#include "InputSystem.h"
#include "..\Imgui\imgui.h"
#include <iostream>

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
	
}

Vector3 InputSystem::GetMousePos() const
{
	return Vector3{ (float)(_p.x - (EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth()) / 2.0f),
	  (float)(EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2.0f) - _p.y, 1.0f };
}

void InputSystem::Exit()
{

}