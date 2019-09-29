#pragma once
#include "KeyCode.h"
#include <windows.h>
#include "Engine/FrameRateController.h"

class InputSystem
{
public:
	void Init();
	void Update();
	void Exit();

	bool KeyDown(KeyCode key);
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];


};