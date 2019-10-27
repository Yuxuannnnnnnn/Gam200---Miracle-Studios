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

	Engine(HINSTANCE hInstance, int nCmdShow):
		_loop{true},
		_console{ new Console()}, //Create a Logging console
		_windowSystem{ new WindowsSystem(hInstance, nCmdShow) }, //Create Window object in it
		_imguiSystem{ new ImguiSystem(_windowSystem->getWindow()) },


		_inputSystem{ new InputSystem() },
		_logicSystem{ new LogicSystem() },
		_graphicsSystem{ new GraphicsSystem() }, 


		_gameObjectFactory{ new GameObjectFactory() }
	{}

	void Init();
	void Update();
	int Exit();

private:

	bool _loop; //for engine update loop

public:

	Console* _console;
	WindowsSystem* _windowSystem;
	ImguiSystem* _imguiSystem;


	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	GraphicsSystem* _graphicsSystem;


	GameObjectFactory* _gameObjectFactory;


};

