#pragma once

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "KeyCode.h"
#include <windows.h>
#include "SystemWindows/WindowsSystem.h"
class InputSystem
{
	float _windowWidth;
	float _windowHeight;

	std::map<std::string, KeyCode> Map_KeyCode;
public:
	KeyCode StringToKeycode(const char* str);

	bool KeyDown(KeyCode key);
	bool KeyHold(KeyCode key);
	bool KeyRelease(KeyCode key);

	void Init();
	void Update(Window& window);
	void Exit();

	Vector3 GetMousePos() const;

	void SetWindowSize(float width, float height);
private:

	void InterruptCheck();

	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
	POINT _p;

};

#endif

