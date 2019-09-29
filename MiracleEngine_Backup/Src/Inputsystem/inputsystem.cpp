#include "InputSystem.h"
#include "..\Imgui\imgui.h"


bool InputSystem::KeyDown(KeyCode key)
{
	return _currBuffer[key] & 0x80;
}

void InputSystem::Init()
{

}

void InputSystem::Update()
{
	PrevTime = Time::now();


	_frameController.UpdateFrameTime();

	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	GetKeyboardState(_currBuffer);


	CurrTime = Time::now();

	FrameTime = std::chrono::duration_cast<ms>(CurrTime - PrevTime);

	ImGui::Text("Input FPS: %.8f ", (FrameTime / FrameRateController::GetFrameRate() * 100));
}

void InputSystem::Exit()
{

}