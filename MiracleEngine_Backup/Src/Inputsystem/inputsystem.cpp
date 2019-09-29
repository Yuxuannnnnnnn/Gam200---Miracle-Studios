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

void InputSystem::Update()
{
	FrameRateController::GetInstance().StartTimeCounter();

	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	GetKeyboardState(_currBuffer);

	//float time = ((FrameTime.count()* 1000 / (FrameRateController::GetInstance().GetFrameTimeMS().count() * 1000)) * 100);

	float time = FrameRateController::GetInstance().EndTimeCounter() / FrameRateController::GetInstance().GetFrameTime() * 100;
	ImGui::Text("Input per Frame Percentage: %.3f %", time);

}

void InputSystem::Exit()
{

}