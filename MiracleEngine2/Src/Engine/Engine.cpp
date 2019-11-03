#include "PrecompiledHeaders.h"




void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

	_inputSystem->Init();	//does nothing?
	//_logicSystem->Init();	// does nothing for now
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

			_performanceUsage->PrintPerformanceUsage();

			double dt = _frameRateControl->UpdateFrameTime();
			int accumlatedframes = _frameRateControl->GetSteps();

			_performanceUsage->PerFrameTime = _frameRateControl->GetFrameTime();
			_performanceUsage->FPS = _frameRateControl->GetFPS();


			if (!_windowSystem->Update()) //Update the window Object - reads all messages received in this window objects
			{
				_gameStateManager->SetNextGameState(GameStateId::GS_QUIT);
				return;
			}

			_frameRateControl->StartTimeCounter();
			_inputSystem->Update(_windowSystem->getWindow());
			_performanceUsage->InputFrameTime = _frameRateControl->EndTimeCounter();

			/*if (_inputSystem->KeyRelease(KEYB_Z))
				std::cout << "Z Released";
			*/

			// Logic
			_frameRateControl->StartTimeCounter();
			_logicSystem->Update(dt);
			_performanceUsage->LogicFrameTime = _frameRateControl->EndTimeCounter();

			// Phy & Coll - Changes the Game State - Calculate GameOver? - Need to pass in GameStateManager?
			_frameRateControl->StartTimeCounter();
			if (accumlatedframes)
			{
				double fixedDt = _frameRateControl->GetLockedDt();

				while (accumlatedframes)
				{
					_physicsSystem->Update(fixedDt);
					--accumlatedframes;
				}

				_gameObjectFactory->UpdateDestoryObjects();
			}
			_performanceUsage->PhysicFrameTime = _frameRateControl->EndTimeCounter();
			

			// Audio
			_frameRateControl->StartTimeCounter();
			_audioSystem->Update();
			_performanceUsage->AudioFrameTime = _frameRateControl->EndTimeCounter();

			_frameRateControl->StartTimeCounter();
			_imguiSystem->UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update
			_performanceUsage->IMGUIFrameTime = _frameRateControl->EndTimeCounter();


			// Graphics
			_frameRateControl->StartTimeCounter();
			_graphicsSystem->Update(dt);
			_performanceUsage->GraphicFrameTime = _frameRateControl->EndTimeCounter();

			_frameRateControl->StartTimeCounter();
			if (open)
			{
				ImGui::ShowDemoWindow(&open); 		//Show Demo Window
			}

			_imguiSystem->Render();  //Renders Imgui Windows - All Imgui windows should be created before this line
			_performanceUsage->IMGUIFrameTime += _frameRateControl->EndTimeCounter();

			::SwapBuffers(_windowSystem->getWindow().get_m_windowDC()); 		// swap double buffer at the end
	//-------------------------------------------------------------------------------------------------------------
		}


		_gameStateManager->UpdateState(); //current state = next state

		_gameObjectFactory->DeleteLevel();

	}



}

int Engine::Exit()
{
	return (int)_windowSystem->Get_msg().wParam;
}
