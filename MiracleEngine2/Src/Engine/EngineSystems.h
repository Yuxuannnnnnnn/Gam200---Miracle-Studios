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
#include "LogicSystem/AiSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"
#include "Tools/DebugTools/FrameRateController.h"
#include "Tools/DebugTools/PerformanceUsage.h"
#include "PhysicSystem/PhysicsSystem.h"
#include "GameObjectFactory/GameObjectPrototype.h"
#include "Audio/AudioSystem.h"
#include "GameObjectFactory/SceneManager.h"


#include "PhysicSystem/ButtonManager.h"
#include "PhysicSystem/CollisionManager.h"
#include "PhysicSystem/RigidBodyManager.h"
#include "PhysicSystem/ImGuizmoManager.h"

#include "TransformManager.h"

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
		_aiSystem{ nullptr },
		_graphicsSystem{ nullptr },
		_physicsSystem{ nullptr },
		_audioSystem{ nullptr },

		_frameRateControl{ nullptr },
		_performanceUsage{ nullptr },

		_gameObjectFactory{ nullptr },
		_prefabFactory{ nullptr },

		_sceneManager{ nullptr },
		_buttonManager{ nullptr },
		_collisionManager{ nullptr },
		_rigidbodyManager{ nullptr },
		_imGuizmoManager{ nullptr },
		_transforManager{ nullptr }
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
		_aiSystem = new AISystem();
		_graphicsSystem = new GraphicsSystem(_windowSystem->getWindow().GetWindowWidth(), _windowSystem->getWindow().GetWindowHeight());
		_physicsSystem = new PhysicsSystem();
		_audioSystem = new AudioSystem();

		_frameRateControl = new FrameRateController(60);	//FrameRateController Set to 60 FPS at start of the Engine
		_performanceUsage = new PerformanceUsage();
		
		_gameObjectFactory = new GameObjectFactory();
		_prefabFactory = new GameObjectPrototype();

		_sceneManager = new SceneManager();

		_buttonManager = new ButtonManager();
		_collisionManager = new CollisionManager();
		_rigidbodyManager = new RigidbodyManager();
		_imGuizmoManager = new ImGuizmoManager();
		_transforManager = new TransformManager();
	}

	virtual ~EngineSystems()
	{
		delete _console;
		delete _windowSystem;
		delete _imguiSystem; //Shutdown ImGui System

		delete _gameStateManager;
		delete _inputSystem;
		delete _logicSystem;
		delete _aiSystem;
		delete _graphicsSystem;
		delete _audioSystem;
		delete _physicsSystem;

		delete _frameRateControl;
		delete _performanceUsage;

		delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory
		delete _sceneManager;


		delete _buttonManager;
		delete _collisionManager;
		delete _rigidbodyManager;
		delete _imGuizmoManager;
		delete _transforManager;

	}


	Console* _console;
	WindowsSystem* _windowSystem;
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
	GameObjectPrototype* _prefabFactory;

	SceneManager* _sceneManager; 

	ButtonManager* _buttonManager;
	CollisionManager* _collisionManager;
	ImGuizmoManager* _imGuizmoManager;
	TransformManager* _transforManager;
	RigidbodyManager* _rigidbodyManager;
};

#define _engineSystems EngineSystems::GetInstance()

#endif
