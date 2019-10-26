#pragma once
#include "GameObjectComponents/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "LogicSystem/LogicSystem.h"
#include "Inputsystem/InputSystem.h"
#include "WindowsSystem/WindowsSystem.h"
class Engine
{
public:

	Engine() :
		_graphicsSystem{ new GraphicsSystem() }, 
		_gameObjectFactory{ new GameObjectFactory() },
		_logicSystem{new LogicSystem()},
		_inputSystem{new InputSystem()}
	{}

	void Init();
	void Update(WindowsSystem& window);
	void Exit();

	GraphicsSystem * _graphicsSystem;
	GameObjectFactory * _gameObjectFactory;
	LogicSystem* _logicSystem;
	InputSystem* _inputSystem;
private:
};

