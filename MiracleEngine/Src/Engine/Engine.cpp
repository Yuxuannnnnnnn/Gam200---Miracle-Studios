#include "PrecompiledHeaders.h"

void Engine::Init()
{
	_graphicsSystem->Init();

	IGameObject* player = _gameObjectFactory->CreateGameObject(PLAYER);
	_gameObjectFactory->DeleteGameObjectID(player->_uId);
}

void Engine::Update()
{
	//_graphicsSystem->Update(_gameObjectFactory->getTransformComponent(), _gameObjectFactory->getGraphicComponent());

	 

}

void Engine::Exit()
{
	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;

}
