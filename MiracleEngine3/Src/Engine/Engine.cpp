#include "PrecompiledHeaders.h"
#include "Tools/EventHandler/EventHandler.h"
#include "GraphicsSystem/GraphicsSystem.h"


void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

	_inputSystem->Init();	//does nothing?
	//_logicSystem->Init();	// does nothing for now
	//_PhysicsSystem->Init();
	//_AudioSystem->Init();
	
	//_sceneManager->ChangeScene(Scenes::LEVEL1);

//-------------------------------------------------------------

}


void Engine::Update()
{
	bool open = true; //for imgui show demo, to be deleted later

	//_sceneManager->ChangeScene(Scenes::LEVEL1);
	_sceneManager->ChangeScene(Scenes::MAIN_MENU);

	_gameObjectFactory->De_SerialiseLevel("hello.json");

	while (_sceneManager->GetCurrentScene() != Scenes::QUIT)	//GameState Logic Starts here
	{

		double dt = _frameRateControl->UpdateFrameTime();
		int accumlatedframes = _frameRateControl->GetSteps();

		//_gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");
			//------Systems update here----- Please do not change the Order of the Systems Update--------------------------

		if (!_windowSystem->Update()) //Update the window Object - reads all messages received in this window objects
		{
			//_gameStateManager->SetNextGameState(GameStateId::GS_QUIT); 
			return;
		}

#ifdef LEVELEDITOR
		_frameRateControl->StartTimeCounter();
		_imguiSystem->UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update
		_performanceUsage->IMGUIFrameTime = _frameRateControl->EndTimeCounter();

		_performanceUsage->PrintPerformanceUsage();
		_performanceUsage->PerFrameTime = _frameRateControl->GetFrameTime();
		_performanceUsage->FPS = _frameRateControl->GetFPS();


		_frameRateControl->StartTimeCounter();
		_inputSystem->Update(_windowSystem->getWindow());
		EventHandler::GetInstance().BroadcastInputEvents();
		_performanceUsage->InputFrameTime = _frameRateControl->EndTimeCounter();

		/*if (_inputSystem->KeyRelease(KEYB_Z))
			std::cout << "Z Released";
		*/

		// Logic
		_frameRateControl->StartTimeCounter();
		if (!_imguiSystem->_pause)
			_logicSystem->Update(dt);
		_aiSystem->Update(dt);
		_performanceUsage->LogicFrameTime = _frameRateControl->EndTimeCounter();

		// Phy & Coll - Changes the Game State - Calculate GameOver? - Need to pass in GameStateManager?
	
		_frameRateControl->StartTimeCounter();
		if (EngineSystems::GetInstance()._imguiSystem->_editorMode)
			_physicsSystem->UpdatePicking();

		if (accumlatedframes)
		{
			double fixedDt = _frameRateControl->GetLockedDt();
			if (!_imguiSystem->_pause)
			{
				while (accumlatedframes)
				{

					_physicsSystem->Update(fixedDt);
					EventHandler::GetInstance().BroadcastCollisionEvents();
					--accumlatedframes;
				}
			}
		}
		if (EngineSystems::GetInstance()._imguiSystem->_editorMode)
			_physicsSystem->UpdateDraw();

		_performanceUsage->PhysicFrameTime = _frameRateControl->EndTimeCounter();

		

		// Audio
		_frameRateControl->StartTimeCounter();
		if (!_imguiSystem->_pause)
			_audioSystem->Update();
		_performanceUsage->AudioFrameTime = _frameRateControl->EndTimeCounter();

		// Graphics
		_frameRateControl->StartTimeCounter();
		_graphicsSystem->Update(dt);
		_performanceUsage->GraphicFrameTime = _frameRateControl->EndTimeCounter();

		// example to draw debug line and circle, to remove later
		/*DebugRenderer::GetInstance().DrawLine(-200, 200, 50, 50);
		DebugRenderer::GetInstance().DrawCircle(50, 50, 50);*/

		_frameRateControl->StartTimeCounter();
		_imguiSystem->Render();  //Renders Imgui Windows - All Imgui windows should be created before this line
		_performanceUsage->IMGUIFrameTime += _frameRateControl->EndTimeCounter();
#else

		_inputSystem->Update(_windowSystem->getWindow());
		_physicsSystem->UpdateButtons();
		EventHandler::GetInstance().BroadcastInputEvents();


		if (accumlatedframes)
		{
			double fixedDt = _frameRateControl->GetLockedDt();

			while (accumlatedframes)
			{
				_logicSystem->Update(dt);
				_aiSystem->Update(dt);
				_physicsSystem->Update(fixedDt);
				EventHandler::GetInstance().BroadcastCollisionEvents();
				--accumlatedframes;
			}
		}


		_audioSystem->Update();
		_graphicsSystem->Update(dt);

#endif

		EventHandler::GetInstance().BroadcastObjectEvents();
		::SwapBuffers(_windowSystem->getWindow().get_m_windowDC()); 		// swap double buffer at the end
//-------------------------------------------------------------------------------------------------------------
	}

	_gameObjectFactory->DeleteLevel();
}

int Engine::Exit()
{
	return (int)_windowSystem->Get_msg().wParam;
}
