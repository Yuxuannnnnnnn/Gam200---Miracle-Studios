#pragma once
#include "KeyCode.h"
#include <windows.h>
#include "WindowsSystem/WindowsSystem.h"
class InputSystem
{
public:
	void Init();
	void Update(WindowsSystem& window);
	void Exit();

	bool KeyDown(KeyCode key);
	POINT GetMousePos() const;
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
	POINT _p;

};