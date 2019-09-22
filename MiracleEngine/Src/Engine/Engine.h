#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "GameObjectComponents/GameObjectFactory.h"


class Engine
{
public:

	Engine()
		:_graphicsSystem{ new GraphicsSystem }, _gameObjectFactory{new GameObjectFactory}
	{}

	void Init();
	void Update();
	void Exit();

	GraphicsSystem * _graphicsSystem;
	GameObjectFactory * _gameObjectFactory;
};

