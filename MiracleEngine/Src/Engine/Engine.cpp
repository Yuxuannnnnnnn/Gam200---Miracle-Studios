#include "PrecompiledHeaders.h"

void Engine::Init()
{
	_gameObjectFactory->Init();
	//_logicSystem->Init();
	_graphicsSystem->Init();

	GameObject* player = _gameObjectFactory->CreateGameObject(TYPE_PLAYER);
	_gameObjectFactory->DeleteGameObjectID(player->_uId);

	
}


void Engine::Update()
{
// Input
	_gameObjectFactory->Update();
// Logic
	using LogicCompMap = std::unordered_map < size_t, LogicComponent* >;
	LogicCompMap temp = _gameObjectFactory->getLogicComponent();
	LogicCompMap::iterator itr = temp.begin();
	while (itr != temp.end())
	{
		// itr->second->Update(); // supposed to call each GO's logicComp and run it's update
		++itr;
	}
// Phy & Coll

// Audio

// Graphics
	//_graphicsSystem->Update(_gameObjectFactory->getTransformComponent(), _gameObjectFactory->getGraphicComponent());

}

void Engine::Exit()
{
	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;

}
