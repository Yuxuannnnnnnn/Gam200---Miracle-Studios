#pragma once
#include "EngineSystems.h"

#define PAUSE 0

class Engine
{
public:

	Engine(HINSTANCE hInstance, int nCmdShow) 	
	{
		EngineSystems::GetInstance().Init(hInstance, nCmdShow);
		_console = EngineSystems::GetInstance()._console;
		_windowSystem = EngineSystems::GetInstance()._windowSystem;
		_imguiSystem = EngineSystems::GetInstance()._imguiSystem;

		_gameStateManager = EngineSystems::GetInstance()._gameStateManager;

		_inputSystem = EngineSystems::GetInstance()._inputSystem;
		_logicSystem = EngineSystems::GetInstance()._logicSystem;
		_aiSystem = EngineSystems::GetInstance()._aiSystem;
		_graphicsSystem = EngineSystems::GetInstance()._graphicsSystem;
		_physicsSystem = EngineSystems::GetInstance()._physicsSystem;
		_audioSystem = EngineSystems::GetInstance()._audioSystem;
		_frameRateControl = EngineSystems::GetInstance()._frameRateControl;
		_performanceUsage = EngineSystems::GetInstance()._performanceUsage;
		_gameObjectFactory = EngineSystems::GetInstance()._gameObjectFactory;
	}

	void Init();
	void Update();
	int Exit();


public:

	WindowsSystem* _windowSystem;
	Console* _console;
	ImguiSystem* _imguiSystem;

	GameStateManager* _gameStateManager;

	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	AISystem* _aiSystem;
	GraphicsSystem* _graphicsSystem;
	PhysicsSystem* _physicsSystem;
	AudioSystem* _audioSystem;


	FrameRateController* _frameRateControl;
	PerformanceUsage* _performanceUsage;

	GameObjectFactory* _gameObjectFactory;

};

