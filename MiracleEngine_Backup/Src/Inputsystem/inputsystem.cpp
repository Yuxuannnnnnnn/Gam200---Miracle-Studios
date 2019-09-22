#include "InputSystem.h"


bool InputSystem::KeyDown(KeyCode key)
{
	return _currBuffer[key] & 0x80;
}

void InputSystem::Init()
{

}

void InputSystem::Update()
{
	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	GetKeyboardState(_currBuffer);
}

void InputSystem::Exit()
{

}