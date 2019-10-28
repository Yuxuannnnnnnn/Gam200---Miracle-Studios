#pragma once
#include "GameObjectFactory/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphicsSystem/DebugRenderer.h"
#include "LogicSystem/LogicSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"

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


	GameObjectFactory* _gameObjectFactory;

};

