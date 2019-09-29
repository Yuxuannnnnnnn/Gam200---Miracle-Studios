#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "FrameRateController.h"
#include "../Inputsystem/InputSystem.h"
#include "PhysicSystem/Physics.h"


class Engine
{
public:
	void Init();
	void Update();
	void Exit();

	
	GraphicsSystem* _graphicSystem;
	InputSystem* _inputSystem;
	Physics* _physicSystem;

	bool keypressed;
};

