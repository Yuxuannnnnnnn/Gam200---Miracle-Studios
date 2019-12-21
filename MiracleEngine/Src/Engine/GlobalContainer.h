#ifndef _GLOBAL_CONTAINER_H
#define _GLOBAL_CONTAINER_H

#include "Interfaces/ISingleton.h"

#include "Windows/Console.h"
#include "Windows/WindowsSystem.h"

#include "Editor/ImguiSystem.h"
#include "Tools/Debug/PerformanceUsage.h"
#include "Editor/ImGuizmoManager.h"

#include "Systems/AnimationSystem.h"
#include "Systems/AudioSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/LogicSystem.h"
#include "Systems/PhysicsSystem.h"


#include "Managers/TransformManager.h"
#include "Managers/RigidBodyManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/CameraManager.h"
#include "Managers/ButtonManager.h"

#include "Factory.h"
#include "SceneManager.h"

//tobe delete
#include "GameObjectFactory.h"
#include "GameObjectPrototype.h"
#include "Tools/Time/FrameRateController.h"
#include "HelperClasses/Logic/AiSystem.h"


#define LEVELEDITOR	1

class GlobalContainer final : public ISingleton<GlobalContainer>
{
public:
	GlobalContainer() :
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
		_logicSystem = new LogicSystem();
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

	virtual ~GlobalContainer()
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

#define _GlobalContainer GlobalContainer::GetInstance()

#define MyConsole (*GlobalContainer::GetInstance()._console)
#define MyWindowsSystem (*GlobalContainer::GetInstance()._windowSystem)
#define MyImguiSystem (*GlobalContainer::GetInstance()._imguiSystem)
#define MyImGuizmoManager (*GlobalContainer::GetInstance()._imGuizmoManager)

#define MyInputSystem (*GlobalContainer::GetInstance()._inputSystem)
#define MyLogicSystem (*GlobalContainer::GetInstance()._logicSystem)
#define MyGraphicsSystem (*GlobalContainer::GetInstance()._graphicsSystem)
#define MyPhysicsSystem (*GlobalContainer::GetInstance()._physicsSystem)
#define MyAudioSystem (*GlobalContainer::GetInstance()._audioSystem)

#define MyAiSystem (*GlobalContainer::GetInstance()._aiSystem)

#define MyFrameRateController (*GlobalContainer::GetInstance()._frameRateControl)
#define MyPerformanceUsage (*GlobalContainer::GetInstance()._performanceUsage)

#define MyButtonManager (*GlobalContainer::GetInstance()._buttonManager)
#define MyCollisionManager (*GlobalContainer::GetInstance()._collisionManager)
#define MyRigidbodyManager (*GlobalContainer::GetInstance()._rigidbodyManager)
#define MyTransformManager (*GlobalContainer::GetInstance()._transforManager)

#define MyGameObjectFactory (*GlobalContainer::GetInstance()._gameObjectFactory)
#define MyPrototypeFactory (*GlobalContainer::GetInstance()._prefabFactory)

#define MySceneManager (*GlobalContainer::GetInstance()._sceneManager)

#endif
