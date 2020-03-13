#ifndef _ENGINE_SYSTEMS_H
#define _ENGINE_SYSTEMS_H

#include "Tools/ISingleton.h"
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
#include "SystemAudio/AudioSystem.h"
#include "Tools/Resource/ResourceManager.h"
#include "Factory.h"
#include "SystemAnimation/AnimationSystem.h"
#include "SystemParticle/ParticleSystem.h"
#include "SystemCamera/CameraSystem.h"    
#include "Editor/ImGuizmoManager.h"
#include "GameObject/ComponentManager.h"
#include "Editor/ImguiSystem.h"
#include "SystemWindows/WindowsSystem.h"
#include "SystemWindows/Console.h"

#define LEVELEDITOR	1
#define DEBUGOUTPUT 0

class EngineSystems final : public ISingleton<EngineSystems>
{
public:
	EngineSystems() :
		_console{ nullptr },
		_windowSystem{ nullptr },
		_frameRateControl{ nullptr },

		_factory{ nullptr },
		_componentManager{ nullptr },

		_logicSystem{ nullptr },
		_scriptSystem{ nullptr },
		_aiSystem{ nullptr },

		_inputSystem{ nullptr },
		_cameraSystem{ nullptr },
		_physicsSystem{ nullptr },
		_audioSystem{ nullptr },
		_animationSystem{ nullptr },
		_graphicsSystem{ nullptr },

		_imguiSystem{ nullptr },
		_imGuizmoManager{ nullptr },

		_resourceManager{ nullptr }
		
	{
	}

	void Init(HINSTANCE hInstance, int nCmdShow)
	{
		_console = new Console(); //Create a Logging console
		_windowSystem = new WindowsSystem(hInstance, nCmdShow); //Create Window object in it
		_frameRateControl = new FrameRateController(60);	//FrameRateController Set to 60 FPS at start of the Engine

		_factory = new Factory;
		_componentManager = new ComponentManager();

		_logicSystem = new LogicSystem();
		_scriptSystem = new ScriptSystem();
		_aiSystem = new AISystem();
		

		_inputSystem = new InputSystem();
		_cameraSystem = new CameraSystem();
		_physicsSystem = new PhysicsSystem();
		_audioSystem = new AudioSystem();
		_animationSystem = new AnimationSystem();
		_graphicsSystem = new GraphicsSystem();
		
#ifdef LEVELEDITOR
		_imGuizmoManager = new ImGuizmoManager();
		_imguiSystem = new ImguiSystem(_windowSystem->getWindow());

		_resourceManager = new ResourceManager(true);
#else
		_resourceManager = new ResourceManager();
#endif
	}

	virtual ~EngineSystems()
	{
		delete _console;
		delete _windowSystem;
		delete _frameRateControl;

		delete _factory;
		delete _componentManager;

		delete _logicSystem;
		delete _scriptSystem;
		delete _aiSystem;

		delete _inputSystem;
		delete _cameraSystem;
		delete _physicsSystem;
		delete _audioSystem;
		delete _animationSystem;
		delete _graphicsSystem;
		
		delete _imGuizmoManager;
		delete _imguiSystem; //Shutdown ImGui System
		
		delete _resourceManager;
	}


	Console* _console;
	WindowsSystem* _windowSystem;
	FrameRateController* _frameRateControl;

	Factory* _factory;
	ComponentManager* _componentManager;

	LogicSystem* _logicSystem;
	ScriptSystem* _scriptSystem;
	AISystem* _aiSystem;

	
	InputSystem* _inputSystem;
	CameraSystem* _cameraSystem;
	PhysicsSystem* _physicsSystem;
	AudioSystem* _audioSystem;
	AnimationSystem* _animationSystem;
	GraphicsSystem* _graphicsSystem;
	
	ImguiSystem* _imguiSystem;
	ImGuizmoManager* _imGuizmoManager;
	
	ResourceManager* _resourceManager;
};

#define _engineSystems EngineSystems::GetInstance()

#define MyConsole (*EngineSystems::GetInstance()._console)
#define MyWindowsSystem (*EngineSystems::GetInstance()._windowSystem)
#define MyFrameRateController (*EngineSystems::GetInstance()._frameRateControl)

#define MyFactory (*EngineSystems::GetInstance()._factory)
#define MyComponentManger (*EngineSystems::GetInstance()._componentManager)

#define MyLogicSystem (*EngineSystems::GetInstance()._logicSystem)
#define MyAiSystem (*EngineSystems::GetInstance()._aiSystem)

#define MyInputSystem (*EngineSystems::GetInstance()._inputSystem)
#define MyCameraSystem (*EngineSystems::GetInstance()._cameraSystem)
#define MyPhysicsSystem (*EngineSystems::GetInstance()._physicsSystem)
#define MyAudioSystem (*EngineSystems::GetInstance()._audioSystem)
#define MyAnimationSystem (*EngineSystems::GetInstance()._animationSystem)
#define MyGraphicsSystem (*EngineSystems::GetInstance()._graphicsSystem)

#define MyImguiSystem (*EngineSystems::GetInstance()._imguiSystem)
#define MyImGuizmoManager (*EngineSystems::GetInstance()._imGuizmoManager)

#define MyResourceManager (*EngineSystems::GetInstance()._resourceManager)

#endif
