#include "PrecompiledHeaders.h"

void Engine::Init()
{
//Please do not change the Order of the Systems Initialisation
	_imguiSystem->Init();

	_inputSystem->Init();
	_logicSystem->Init(); // does nothing for now
	//_PhysicsSystem->Init();
	//_AudioSystem->Init();
	_graphicsSystem->Init();
	
	_gameObjectFactory->Init();
//-------------------------------------------------------------

	// TESTING GO creation 
	if (true)
	{
		_gameObjectFactory->TEST_AddGameObjects();
		_gameObjectFactory->TEST_DisplayAllGameObj();
	}
}


void Engine::Update(WindowsSystem& window)
{
	_imguiSystem->UpdateFrame(); //Calls new frames for Imgui every loop

	// TESTING mem leak for objects
	if (true)
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

	_imguiSystem->Render(); //Renders Imgui Windows and clears opengl buffer

}

void Engine::Exit()
{
	delete _imguiSystem; //Shutdown ImGui System

	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;

}
