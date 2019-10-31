#include "PrecompiledHeaders.h"




void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

	_inputSystem->Init();	//does nothing?
	_logicSystem->Init();	// does nothing for now
	//_PhysicsSystem->Init();
	//_AudioSystem->Init();
	
//-------------------------------------------------------------
}


void Engine::Update()
{
	bool open = true; //for imgui show demo, to be deleted later


	while (_gameStateManager->CheckIfCurrStateQuit())	//GameState Logic Starts here
	{

		_gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");


		while (_gameStateManager->CheckIfCurrNextStateSame())	//In Game Level
		{
			//WindowsSystem -> InputSystem -> Logic System -> Physics System -> AudioSytem -> ImguiSystem UpdateFrame -> GraphicSystem ->  ImguiSystem Render
			//------Systems update here----- Please do not change the Order of the Systems Update--------------------------

			double dt = _frameRateControl->UpdateFrameTime();
			int accumlatedframes = _frameRateControl->GetSteps();

			if (!_windowSystem->Update()) //Update the window Object - reads all messages received in this window objects
			{
				_gameStateManager->SetNextGameState(GameStateId::GS_QUIT);
				return;
			}


			_inputSystem->Update(_windowSystem->getWindow());

			/*if (_inputSystem->KeyRelease(KEYB_Z))
				std::cout << "Z Released";
			*/

			// Logic
			_logicSystem->Update(_gameObjectFactory->getLogicComponent(), _gameObjectFactory, _inputSystem);

			// Phy & Coll - Changes the Game State - Calculate GameOver? - Need to pass in GameStateManager?
			if (accumlatedframes)
			{
				double fixedDt = _frameRateControl->GetLockedDt();

				while (accumlatedframes)
				{
					_physicsSystem->Update(fixedDt);
					--accumlatedframes;
				}
			}



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


		_gameStateManager->UpdateState(); //current state = next state

		_gameObjectFactory->DeleteLevel();

	}



}

int Engine::Exit()
{
	delete _console;
	delete _windowSystem;
	delete _imguiSystem; //Shutdown ImGui System

	delete _gameStateManager;
	delete _inputSystem;
	delete _logicSystem;
	delete _graphicsSystem;
	delete _gameObjectFactory; 	//delete all objects in the gameObjectFactory


	return (int)_windowSystem->Get_msg().wParam;
}
