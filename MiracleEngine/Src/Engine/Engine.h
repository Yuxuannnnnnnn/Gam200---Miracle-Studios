#pragma once
#include "GameObjectComponents/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "LogicSystem/LogicSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"

#include "ImguiSystem.h"



class Engine
{
public:

	Engine() :
		_imguiSystem{ new ImguiSystem() },

		_inputSystem{ new InputSystem() },
		_logicSystem{ new LogicSystem() },
		_graphicsSystem{ new GraphicsSystem() }, 

		_gameObjectFactory{ new GameObjectFactory() }
	{}

	void Init();
	void Update(WindowsSystem& window);
	void Exit();


	ImguiSystem* _imguiSystem;

	InputSystem* _inputSystem;
	LogicSystem* _logicSystem;
	GraphicsSystem* _graphicsSystem;

	GameObjectFactory* _gameObjectFactory;

private:
};

