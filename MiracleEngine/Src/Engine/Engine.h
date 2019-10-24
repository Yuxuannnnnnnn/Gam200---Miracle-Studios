#pragma once
#include "GameObjectComponents/GameObjectFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"

class Engine
{
public:

	Engine() :
		_graphicsSystem{ new GraphicsSystem() }, 
		_gameObjectFactory{ new GameObjectFactory() }
	{}

	void Init();
	void Update();
	void Exit();

	GraphicsSystem * _graphicsSystem;
	GameObjectFactory * _gameObjectFactory;
	//LogicSystem* _logicSystem;

private:
};

