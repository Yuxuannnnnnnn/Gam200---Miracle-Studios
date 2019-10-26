#include "PrecompiledHeaders.h"

void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

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


void Engine::Update()
{
	bool loop = true;

	while (loop)
	{
		loop = _windowSystem->Update(); //Update the window Object - reads all messages received in this window objects

//--Systems update here----- Please do not change the Order of the Systems Update--------------------------
		_imguiSystem->UpdateFrame(); //Calls new frames for Imgui every loop

		// TESTING mem leak for objects
		if (false)
		{
			_gameObjectFactory->TEST_AddGameObjects();
			_gameObjectFactory->TEST_DisplayAllGameObj();
			_gameObjectFactory->TEST_DeleteAllGameObjects();
			_gameObjectFactory->Update();
		}

		_inputSystem->Update(_windowSystem->getWindow());

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

		//Show Demo Window
		ImGui::ShowDemoWindow();


		//All Imgui windows should be created before this line
		//Renders Imgui Windows and clears opengl buffer
		_imguiSystem->Render(); 

		// swap double buffer at the end
		::SwapBuffers(_windowSystem->getWindow().get_m_windowDC());
//-------------------------------------------------------------------------------------------------------------

	}



}

int Engine::Exit()
{

	delete _graphicsSystem;

	delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory

	delete _imguiSystem; //Shutdown ImGui System

	int wparam = _windowSystem->Get_msg().wParam;
	return (int) wparam;
}
