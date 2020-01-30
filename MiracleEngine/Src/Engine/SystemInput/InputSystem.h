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

	std::unordered_set<size_t> _buttonHover;
	std::unordered_set<size_t> _buttonPressed;
public:
	KeyCode StringToKeycode(const char* str);

	bool KeyDown(KeyCode key);
	bool KeyHold(KeyCode key);
	bool KeyRelease(KeyCode key);

	void Init();
	void Update(Window& window);
	void Exit();

	Vector3 GetMouseWorldPos();
	Vector3 GetMouseScreenPos();

	void SetWindowSize(float width, float height);
private:

	void InterruptCheck();

	void ButtonUpdate();

	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
	POINT _p;

};

#endif

