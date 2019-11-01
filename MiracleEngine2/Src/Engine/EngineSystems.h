///////////////////////////////////////////////////////////////////////////////////////
//
//	EngineSystems.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _ENGINE_SYSTEMS_H
#define _ENGINE_SYSTEMS_H

#include "../ISingleton.h"

#include "GameObjectFactory/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphicsSystem/DebugRenderer.h"
#include "LogicSystem/LogicSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"
#include "Tools/DebugTools/FrameRateController.h"
#include "PhysicSystem/PhysicsSystem.h"
#include "GameObjectFactory/GameObjectPrototype.h"

#include "ImguiSystem.h"
#include "WindowsSystem.h"
#include "Console.h"


class EngineSystems final : public ISingleton<EngineSystems>
{
public:
	EngineSystems() :
		_console{ nullptr },
		_windowSystem{ nullptr },
		_imguiSystem{ nullptr },
		_gameStateManager{ nullptr },
		_inputSystem{ nullptr },
		_logicSystem{ nullptr },
		_graphicsSystem{ nullptr },
		_physicsSystem{ nullptr },
		_frameRateControl{ nullptr },
		_gameObjectFactory{ nullptr },
		_prefabFactory{ nullptr }
	{
	}

	void Init(HINSTANCE hInstance, int nCmdShow)
	{
		_console = new Console(); //Create a Logging console
		_windowSystem = new WindowsSystem(hInstance, nCmdShow); //Create Window object in it
		_imguiSystem = new ImguiSystem(_windowSystem->getWindow());

		_gameStateManager = new GameStateManager();

		_inputSystem = new InputSystem();
		_logicSystem =  new LogicSystem();
		_graphicsSystem = new GraphicsSystem(_windowSystem->getWindow().GetWindowWidth(), _windowSystem->getWindow().GetWindowHeight());
		_physicsSystem = new PhysicsSystem();
		_frameRateControl = new FrameRateController(60);	//FrameRateController Set to 60 FPS at start of the Engine
		_gameObjectFactory = new GameObjectFactory();

		_prefabFactory = new GameObjectPrototype();
	}

	virtual ~EngineSystems()
	{
		delete _console;
		delete _windowSystem;
		delete _imguiSystem; //Shutdown ImGui System

		delete _gameStateManager;
		delete _inputSystem;
		delete _logicSystem;
		delete _graphicsSystem;
		delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory

		delete _physicsSystem;
		delete _frameRateControl;
	}


	Console* _console;
	WindowsSystem* _windowSystem;
	ImguiSystem* _imguiSystem;

	GameStateManager* _gameStateManager;

	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	GraphicsSystem* _graphicsSystem;
	PhysicsSystem* _physicsSystem;

	FrameRateController* _frameRateControl;

	GameObjectFactory* _gameObjectFactory;

	GameObjectPrototype* _prefabFactory;
};



#endif