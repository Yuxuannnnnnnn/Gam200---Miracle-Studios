#pragma once
#include "KeyCode.h"
#include <windows.h>
#include "WindowsSystem/WindowsSystem.h"
class InputSystem
{
public:

	bool KeyDown(KeyCode key);
	bool KeyHold(KeyCode key);
	bool KeyRelease(KeyCode key);

	void Init();
	void Update(Window& window);
	void Exit();


	POINT GetMousePos() const;
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
	POINT _p;

};