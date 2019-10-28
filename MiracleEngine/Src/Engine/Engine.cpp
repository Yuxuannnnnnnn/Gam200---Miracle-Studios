#include "PrecompiledHeaders.h"




void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

	_inputSystem->Init();	//does nothing?
	_logicSystem->Init();	// does nothing for now
	//_PhysicsSystem->Init();
	//_AudioSystem->Init();
	
//-------------------------------------------------------------

	// TESTING GO creation 
	//if (false)
	//{
	//	_gameObjectFactory->FileRead_Level("./Resources/TextFiles/TestLevel.txt");
	//	_gameObjectFactory->TEST_AddGameObjects();
	//	_gameObjectFactory->TEST_DisplayAllGameObj();
	//}
}


void Engine::Update()
{
	bool open = true; //for imgui show demo, to be deleted later
	bool _loop = true;

	//while (_gameStateManager->GetCurrState() != GameStateId::GS_QUIT)
	//{
	//
	//}

	while (_loop)
	{


		_gameObjectFactory->FileRead_Level("./Resources/TextFiles/TestLevel.txt");


		while (_loop)	//In Game Level
		{
		//WindowsSystem -> InputSystem -> Logic System -> Physics System -> AudioSytem -> ImguiSystem UpdateFrame -> GraphicSystem ->  ImguiSystem Render
		//------Systems update here----- Please do not change the Order of the Systems Update--------------------------

			// TESTING mem leak for objects
			//if (false)
			//{
			//	_gameObjectFactory->TEST_AddGameObjects();
			//	_gameObjectFactory->FileRead_Level("./Resources/TextFiles/TestLevel.txt");
			//	_gameObjectFactory->TEST_DisplayAllGameObj();
			//	_gameObjectFactory->TEST_DeleteAllGameObjects();
			//	//_gameObjectFactory->Update();
			//}
			_loop = _windowSystem->Update(); //Update the window Object - reads all messages received in this window objects

			_inputSystem->Update(_windowSystem->getWindow());

			/*if (_inputSystem->KeyRelease(KEYB_Z))
				std::cout << "Z Released";
			*/

			// Logic
			//if (false)
			//{
			//	using LogicCompMap = std::unordered_map < size_t, LogicComponent* >;
			//	LogicCompMap temp = _gameObjectFactory->getLogicComponent();
			//	LogicCompMap::iterator itr = temp.begin();
			//	while (itr != temp.end())
			//	{
			//		// TODO-Brandon, shift this to the actual LogicSystem.h Update()
			//		itr->second->Update(); // supposed to call each GO's logicComp and run it's update
			//		++itr;
			//	}
			//}

			// Phy & Coll

			// Audio

			_imguiSystem->UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update

			// Graphics
			_graphicsSystem->Update(_gameObjectFactory->getGraphicComponent(), _gameObjectFactory->getTransformComponent());


			// example to draw debug line and circle, to remove later
			DebugRenderer::GetInstance().DrawLine(-200, 200, 50, 50);
			DebugRenderer::GetInstance().DrawCircle(50, 50, 50);

			if (open)
			{
				ImGui::ShowDemoWindow(&open); 		//Show Demo Window
			}

			_imguiSystem->Render();  //Renders Imgui Windows - All Imgui windows should be created before this line

			::SwapBuffers(_windowSystem->getWindow().get_m_windowDC()); 		// swap double buffer at the end
	//-------------------------------------------------------------------------------------------------------------
		}


		_gameObjectFactory->DeleteLevel();

	}



}

int Engine::Exit()
{

	delete _graphicsSystem;

		// inheriting ISingleton, will cause crash from double delete
		// need check how singleton is deleting cause its not running the destructor for GOFac
	delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory

	delete _imguiSystem; //Shutdown ImGui System



	return (int)_windowSystem->Get_msg().wParam;
}
