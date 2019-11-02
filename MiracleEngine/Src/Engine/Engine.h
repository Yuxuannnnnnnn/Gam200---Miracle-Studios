#pragma once
#include "GameObjectFactory/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphicsSystem/DebugRenderer.h"
#include "LogicSystem/LogicSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"
#include "Tools/DebugTools/FrameRateController.h"
#include "Tools/DebugTools/PerformanceUsage.h"
#include "PhysicSystem/Physics.h"

#include "ImguiSystem.h"
#include "WindowsSystem.h"
#include "Console.h"



class Engine
{
public:

	Engine(HINSTANCE hInstance, int nCmdShow) :
		_console{ new Console() }, //Create a Logging console
		_windowSystem{ new WindowsSystem(hInstance, nCmdShow) }, //Create Window object in it
		_imguiSystem{ new ImguiSystem(_windowSystem->getWindow()) },

		_gameStateManager{ new GameStateManager() },

		_inputSystem{ new InputSystem() },
		_logicSystem{ new LogicSystem() },
		_graphicsSystem{ new GraphicsSystem(_windowSystem->getWindow().GetWindowWidth(), 
											_windowSystem->getWindow().GetWindowHeight())},
		_physicsSystem{ new Physics() },

		_frameRateControl{ new FrameRateController(60) },	//FrameRateController Set to 60 FPS at start of the Engine
		_performanceUsage{ new PerformanceUsage() },
		_gameObjectFactory{ new GameObjectFactory() }
	{}

	void Init();
	void Update();
	int Exit();


public:

	Console* _console;
	WindowsSystem* _windowSystem;
	ImguiSystem* _imguiSystem;

	GameStateManager* _gameStateManager;

	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	GraphicsSystem* _graphicsSystem;
	Physics* _physicsSystem;

	FrameRateController* _frameRateControl;
	PerformanceUsage* _performanceUsage;

	GameObjectFactory* _gameObjectFactory;

};

