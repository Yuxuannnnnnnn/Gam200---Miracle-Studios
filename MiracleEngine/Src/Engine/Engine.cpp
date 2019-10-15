#include "PrecompiledHeaders.h"

void Engine::Init()
{
	_graphicsSystem->Init();

	IGameObject* player = _gameObjectFactory->CreateGameObject(PLAYER);
	_gameObjectFactory->DeleteGameObjectID(player->_uId);

	_frameController->Initialize();
}

void Engine::Update()
{
	//_graphicsSystem->Update(_gameObjectFactory->getTransformComponent(), _gameObjectFactory->getGraphicComponent());
	
	double deltaTime = _frameController->UpdateFrameTime();
	(void)deltaTime;

	 

}

void Engine::Exit()
{
	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;


	delete _frameController;
}
