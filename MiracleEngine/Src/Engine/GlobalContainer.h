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
#include "SystemLogic/ScriptSystem/ScriptSystem.h"
#include "SystemInput/InputSystem.h"
#include "SystemWindows/WindowsSystem.h"
#include "Tools/Time/FrameRateController.h"
#include "Editor/PerformanceUsageWindow.h"
#include "SystemPhysics/PhysicsSystem.h"
//#include "GameObjectPrototype.h"
#include "SystemAudio/AudioSystem.h"
#include "SceneManager.h"
#include "Tools/Resource/ResourceManager.h"
#include "Factory.h"
#include "SystemAnimation/AnimationSystem.h"

//#include "SystemPhysics/ButtonManager.h"
//#include "SystemPhysics/CollisionManager.h"
//#include "SystemPhysics/RigidBodyManager.h"
#include "Editor/ImGuizmoManager.h"

#include "GameObject/ComponentManager.h"

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

		_componentManager{ nullptr },

		_inputSystem{ nullptr },
		_logicSystem{ nullptr },
		_scriptSystem{ nullptr },
		_aiSystem{ nullptr },

		_animationSystem{ nullptr },
		_graphicsSystem{ nullptr },
		_physicsSystem{ nullptr },
		_audioSystem{ nullptr },

		_frameRateControl{ nullptr },

		_gameObjectFactory{ nullptr },
		//_prefabFactory{ nullptr },

		_factory{nullptr},

		_sceneManager{ nullptr },
		_imguiSystem{ nullptr },

		//_buttonManager{ nullptr },
		//_collisionManager{ nullptr },
		//_rigidbodyManager{ nullptr },
		_imGuizmoManager{ nullptr },
		_resourceManager{ nullptr }
	{
	}

	void Init(HINSTANCE hInstance, int nCmdShow)
	{
		_console = new Console(); //Create a Logging console
		_windowSystem = new WindowsSystem(hInstance, nCmdShow); //Create Window object in it

		_componentManager = new ComponentManager();

		_audioSystem = new AudioSystem();

		_inputSystem = new InputSystem();
		_logicSystem =  new LogicSystem();
		_scriptSystem = new ScriptSystem();
		_aiSystem = new AISystem();
		_animationSystem = new AnimationSystem();
		_graphicsSystem = new GraphicsSystem(_windowSystem->getWindow().GetWindowWidth(), _windowSystem->getWindow().GetWindowHeight());
		_physicsSystem = new PhysicsSystem();
		

		_frameRateControl = new FrameRateController(60);	//FrameRateController Set to 60 FPS at start of the Engine

		_gameObjectFactory = new GameObjectFactory();
		//_prefabFactory = new GameObjectPrototype();

		_factory = new Factory;

		_sceneManager = new SceneManager();

		//_buttonManager = new ButtonManager();
		//_collisionManager = new CollisionManager();
		//_rigidbodyManager = new RigidbodyManager();

#ifdef LEVELEDITOR
		_imGuizmoManager = new ImGuizmoManager();
		_imguiSystem = new ImguiSystem(_windowSystem->getWindow());
		_resourceManager = new ResourceManager(false);
#else
		_resourceManager = new ResourceManager();
#endif
	}

	virtual ~EngineSystems()
	{
		delete _console;
		delete _windowSystem;
		delete _imguiSystem; //Shutdown ImGui System

		delete _componentManager;

		delete _inputSystem;
		delete _logicSystem;
		delete _scriptSystem;
		delete _aiSystem;
		delete _animationSystem;
		delete _graphicsSystem;
		delete _audioSystem;
		delete _physicsSystem;

		delete _frameRateControl;

		delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory

		delete _factory;

		delete _sceneManager;


		//delete _buttonManager;
		//delete _collisionManager;
		//delete _rigidbodyManager;
		delete _imGuizmoManager;

		delete _resourceManager;
	}


	Console* _console;
	WindowsSystem* _windowSystem;

	ComponentManager* _componentManager;

	AnimationSystem* _animationSystem;
	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	ScriptSystem* _scriptSystem;
	AISystem* _aiSystem;
	GraphicsSystem* _graphicsSystem;
	PhysicsSystem* _physicsSystem;

	AudioSystem* _audioSystem;

	FrameRateController* _frameRateControl;

	GameObjectFactory* _gameObjectFactory;
	//GameObjectPrototype* _prefabFactory;

	Factory* _factory;

	SceneManager* _sceneManager;

	ImguiSystem* _imguiSystem;

	//ButtonManager* _buttonManager;
	//CollisionManager* _collisionManager;
	ImGuizmoManager* _imGuizmoManager;
	//RigidbodyManager* _rigidbodyManager;

	ResourceManager* _resourceManager;
};

#define _engineSystems EngineSystems::GetInstance()

#define MyConsole (*EngineSystems::GetInstance()._console)
#define MyWindowsSystem (*EngineSystems::GetInstance()._windowSystem)
#define MyImguiSystem (*EngineSystems::GetInstance()._imguiSystem)
#define MyImGuizmoManager (*EngineSystems::GetInstance()._imGuizmoManager)

#define MyComponentManger (*EngineSystems::GetInstance()._componentManager)

#define MyInputSystem (*EngineSystems::GetInstance()._inputSystem)
#define MyLogicSystem (*EngineSystems::GetInstance()._logicSystem)
#define MyGraphicsSystem (*EngineSystems::GetInstance()._graphicsSystem)
#define MyPhysicsSystem (*EngineSystems::GetInstance()._physicsSystem)
#define MyAudioSystem (*EngineSystems::GetInstance()._audioSystem)
#define MyAnimationSystem (*EngineSystems::GetInstance()._animationSystem)

#define MyAiSystem (*EngineSystems::GetInstance()._aiSystem)

#define MyFrameRateController (*EngineSystems::GetInstance()._frameRateControl)

//#define MyButtonManager (*EngineSystems::GetInstance()._buttonManager)
//#define MyCollisionManager (*EngineSystems::GetInstance()._collisionManager)
//#define MyRigidbodyManager (*EngineSystems::GetInstance()._rigidbodyManager)

#define MyGameObjectFactory (*EngineSystems::GetInstance()._gameObjectFactory)
//#define MyPrototypeFactory (*EngineSystems::GetInstance()._prefabFactory)

#define MyFactory (*EngineSystems::GetInstance()._factory)

#define MySceneManager (*EngineSystems::GetInstance()._sceneManager)

#define MyResourceManager (*EngineSystems::GetInstance()._resourceManager)

#endif
