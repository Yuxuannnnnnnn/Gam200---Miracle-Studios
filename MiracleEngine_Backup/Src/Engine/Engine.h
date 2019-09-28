#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "FrameRateController.h"
#include "../Inputsystem/InputSystem.h"




class Engine
{
public:
	void Init();
	void Update();
	void Exit();

	GraphicsSystem* _graphicSystem;
	InputSystem* _inputSystem;
	FrameRateController* _frameController;

	bool keypressed;
};


