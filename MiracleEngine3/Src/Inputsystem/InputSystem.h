#pragma once

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

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


	Vector3 GetMousePos() const;
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
	POINT _p;

};

#endif
