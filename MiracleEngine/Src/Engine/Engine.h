#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "GameObjectComponents/GameObjectFactory.h"

#include "FrameRateController.h"

class Engine
{
public:

	Engine()
		:_graphicsSystem{ new GraphicsSystem() }, 
		_gameObjectFactory{new GameObjectFactory() }, 
		_frameController{ new FrameRateController() }
	{}

	void Init();
	void Update();
	void Exit();

	GraphicsSystem * _graphicsSystem;
	GameObjectFactory * _gameObjectFactory;
	FrameRateController* _frameController;

private:
};

