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

#define LEVELEDITOR	1

class EngineSystems final : public ISingleton<EngineSystems>
{
public:
	EngineSystems() :
		_console{ nullptr },
		_windowSystem{ nullptr },

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
		_imguiSystem{ nullptr },

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


		_audioSystem = new AudioSystem();
		_gameStateManager = new GameStateManager();

		_inputSystem = new InputSystem();
		_logicSystem =  new LogicSystem();
		_aiSystem = new AISystem();
		_graphicsSystem = new GraphicsSystem(_windowSystem->getWindow().GetWindowWidth(), _windowSystem->getWindow().GetWindowHeight());
		_physicsSystem = new PhysicsSystem();
		

		_frameRateControl = new FrameRateController(60);	//FrameRateController Set to 60 FPS at start of the Engine

		_gameObjectFactory = new GameObjectFactory();
		_prefabFactory = new GameObjectPrototype();

		_sceneManager = new SceneManager();

		_buttonManager = new ButtonManager();
		_collisionManager = new CollisionManager();
		_rigidbodyManager = new RigidbodyManager();
		_transforManager = new TransformManager();

#ifdef LEVELEDITOR
		_performanceUsage = new PerformanceUsage();
		_imGuizmoManager = new ImGuizmoManager();
		_imguiSystem = new ImguiSystem(_windowSystem->getWindow());
#endif
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

	ImguiSystem* _imguiSystem;

	ButtonManager* _buttonManager;
	CollisionManager* _collisionManager;
	ImGuizmoManager* _imGuizmoManager;
	TransformManager* _transforManager;
	RigidbodyManager* _rigidbodyManager;
};

#define _engineSystems EngineSystems::GetInstance()

#define MyConsole (*EngineSystems::GetInstance()._console)
#define MyWindowsSystem (*EngineSystems::GetInstance()._windowSystem)
#define MyImguiSystem (*EngineSystems::GetInstance()._imguiSystem)
#define MyImGuizmoManager (*EngineSystems::GetInstance()._imGuizmoManager)

#define MyInputSystem (*EngineSystems::GetInstance()._inputSystem)
#define MyLogicSystem (*EngineSystems::GetInstance()._logicSystem)
#define MyGraphicsSystem (*EngineSystems::GetInstance()._graphicsSystem)
#define MyPhysicsSystem (*EngineSystems::GetInstance()._physicsSystem)
#define MyAudioSystem (*EngineSystems::GetInstance()._audioSystem)

#define MyAiSystem (*EngineSystems::GetInstance()._aiSystem)

#define MyFrameRateController (*EngineSystems::GetInstance()._frameRateControl)
#define MyPerformanceUsage (*EngineSystems::GetInstance()._performanceUsage)

#define MyButtonManager (*EngineSystems::GetInstance()._buttonManager)
#define MyCollisionManager (*EngineSystems::GetInstance()._collisionManager)
#define MyRigidbodyManager (*EngineSystems::GetInstance()._rigidbodyManager)
#define MyTransformManager (*EngineSystems::GetInstance()._transforManager)

#define MyGameObjectFactory (*EngineSystems::GetInstance()._gameObjectFactory)
#define MyPrototypeFactory (*EngineSystems::GetInstance()._prefabFactory)

#define MySceneManager (*EngineSystems::GetInstance()._sceneManager)

#endif
