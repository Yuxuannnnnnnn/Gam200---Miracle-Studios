#include "PrecompiledHeaders.h"

void Engine::Init()
{
	_gameObjectFactory->Init();
	//_logicSystem->Init();
	_graphicsSystem->Init();
	_logicSystem->Init(); // does nothing for now

	if (true)
	{
		_gameObjectFactory->TEST_AddGameObjects();
		_gameObjectFactory->TEST_DisplayAllGameObj();
	}
}


void Engine::Update()
{
	if (false)
	{
		_gameObjectFactory->TEST_AddGameObjects();
		_gameObjectFactory->TEST_DisplayAllGameObj();
		_gameObjectFactory->TEST_DeleteAllGameObjects();
		_gameObjectFactory->Update();
		return;
	}
// Input
	_gameObjectFactory->Update();
// Logic
	//using LogicCompMap = std::unordered_map < size_t, LogicComponent* >;
	//LogicCompMap temp = _gameObjectFactory->getLogicComponent();
	//LogicCompMap::iterator itr = temp.begin();
	//while (itr != temp.end())
	//{
	//	// TODO-Brandon, shift this to the actual LogicSystem.h Update()
	//	itr->second->Update(); // supposed to call each GO's logicComp and run it's update
	//	++itr;
	//}
	if (false)
	{
	using LogicCompMap = std::unordered_map < size_t, LogicComponent* >;
	LogicCompMap temp = _gameObjectFactory->getLogicComponent();
	LogicCompMap::iterator itr = temp.begin();
	while (itr != temp.end())
	{
		// TODO-Brandon, shift this to the actual LogicSystem.h Update()
		itr->second->Update(); // supposed to call each GO's logicComp and run it's update
		++itr;
	}
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
