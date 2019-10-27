#include "PrecompiledHeaders.h"

void Engine::Init()
{
	_gameObjectFactory->Init();
	//_logicSystem->Init();
	_inputSystem->Init();
	_graphicsSystem->Init();
	_logicSystem->Init(); // does nothing for now

	// TESTING GO creation 
	if (true)
	{
		_gameObjectFactory->FileRead_Level("./Resources/TextFiles/TestLevel.txt");
		_gameObjectFactory->TEST_AddGameObjects();
		_gameObjectFactory->TEST_DisplayAllGameObj();
	}
}


void Engine::Update(WindowsSystem& window)
{
	// TESTING mem leak for objects
	if (false)
	{
		_gameObjectFactory->TEST_AddGameObjects();
		_gameObjectFactory->TEST_DisplayAllGameObj();
		_gameObjectFactory->TEST_DeleteAllGameObjects();
		_gameObjectFactory->Update();
	}
	// Input
	_inputSystem->Update(window);

	/*if (_inputSystem->KeyRelease(KEYB_Z))
		std::cout << "Z Released";
	*/
	_gameObjectFactory->Update();
	// Logic
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
	_graphicsSystem->Update(_gameObjectFactory->getGraphicComponent());

}

void Engine::Exit()
{
	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;

}
