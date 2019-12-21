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

#include "Tools/ISingleton.h"

#include "GameObjectFactory.h"
#include "SystemGraphics/GraphicsSystem.h"
#include "SystemGraphics/DebugRenderer.h"
#include "SystemLogic/LogicSystem.h"
#include "SystemLogic/AiSystem.h"
#include "SystemInput/InputSystem.h"
#include "SystemWindows/WindowsSystem.h"
#include "Tools/Time/FrameRateController.h"
#include "Editor/PerformanceUsageWindow.h"
#include "SystemPhysics/PhysicsSystem.h"
#include "GameObjectPrototype.h"
#include "SystemAudio/AudioSystem.h"
#include "SceneManager.h"


#include "SystemPhysics/ButtonManager.h"
#include "SystemPhysics/CollisionManager.h"
#include "SystemPhysics/RigidBodyManager.h"
#include "Editor/ImGuizmoManager.h"

#include "TransformManager.h"

#include "Editor/ImguiSystem.h"
#include "SystemWindows/WindowsSystem.h"
#include "SystemWindows/Console.h"

#define LEVELEDITOR	1

class EngineSystems final : public ISingleton<EngineSystems>
{
public:
	EngineSystems() :
		_console{ nullptr },
		_windowSystem{ nullptr },

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
