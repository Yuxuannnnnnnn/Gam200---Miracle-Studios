#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "../Inputsystem/InputSystem.h"
#include "PhysicSystem/Physics.h"

#include "FrameRateController.h"
#include "PhysicSystem/PerformanceUsage.h"
#include "WindowsSystem/WindowsSystem.h"
class Engine
{
public:
	void Init();
	void Update(WindowsSystem& window);
	void Exit();

	
	GraphicsSystem* _graphicSystem;
	InputSystem* _inputSystem;
	Physics* _physicSystem;
	FrameRateController* _fController;
	PerformanceUsage* _pUsage;

	bool keypressed;

	bool _stressTest;
};

