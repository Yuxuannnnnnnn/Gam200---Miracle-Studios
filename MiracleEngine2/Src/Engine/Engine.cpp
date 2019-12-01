#include "PrecompiledHeaders.h"
#include "Tools/EventHandler/EventHandler.h"



void Engine::Init()
{
//--Init replaced by Constructor?---------------------------

	_engineSystems._inputSystem->Init();	//does nothing?
	//_logicSystem->Init();	// does nothing for now
	//_PhysicsSystem->Init();
	//_AudioSystem->Init();
	
	//_sceneManager->ChangeScene(Scenes::LEVEL1);

//-------------------------------------------------------------
}


void Engine::Update()
{
	bool open = true; //for imgui show demo, to be deleted later

	_engineSystems._sceneManager->ChangeScene(Scenes::LEVEL1);
	//_sceneManager->ChangeScene(Scenes::MAIN_MENU);

	//_gameObjectFactory->De_SerialiseLevel("hello.json");

	while (_engineSystems._sceneManager->GetCurrentScene() != Scenes::QUIT)	//GameState Logic Starts here
	{

		//_gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");
			//------Systems update here----- Please do not change the Order of the Systems Update--------------------------

		if (!_engineSystems._windowSystem->Update()) //Update the window Object - reads all messages received in this window objects
		{
			//_gameStateManager->SetNextGameState(GameStateId::GS_QUIT); 
			return;
		}

#ifdef LEVELEDITOR

		_engineSystems._frameRateControl->StartTimeCounter();
		_engineSystems._imguiSystem->UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update
		_engineSystems._performanceUsage->IMGUIFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		_engineSystems._performanceUsage->PrintPerformanceUsage();

		double dt = _engineSystems._frameRateControl->UpdateFrameTime();
		int accumlatedframes = _engineSystems._frameRateControl->GetSteps();


		_engineSystems._performanceUsage->PerFrameTime = _engineSystems._frameRateControl->GetFrameTime();
		_engineSystems._performanceUsage->FPS = _engineSystems._frameRateControl->GetFPS();

		_engineSystems._frameRateControl->StartTimeCounter();


		_engineSystems._inputSystem->Update(_engineSystems._windowSystem->getWindow());
		EventHandler::GetInstance().BroadcastInputEvents();


		_engineSystems._performanceUsage->InputFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		/*if (_inputSystem->KeyRelease(KEYB_Z))
			std::cout << "Z Released";
		*/

		// Logic
		_engineSystems._frameRateControl->StartTimeCounter();

		if (!_engineSystems._imguiSystem->_pause)
		{
			_engineSystems._logicSystem->Update(dt);
		}

		_engineSystems._aiSystem->Update(dt);

		_engineSystems._performanceUsage->LogicFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		// Phy & Coll - Changes the Game State - Calculate GameOver? - Need to pass in GameStateManager?
		_engineSystems._frameRateControl->StartTimeCounter();

		/*if (EngineSystems::GetInstance()._imguiSystem->_editorMode)
			_engineSystems._physicsSystem->UpdatePicking();*/

		if (accumlatedframes)
		{
			double fixedDt = _engineSystems._frameRateControl->GetLockedDt();

			if (!_engineSystems._imguiSystem->_pause)
			{
				while (accumlatedframes)
				{

					_engineSystems._physicsSystem->Update(fixedDt);
					EventHandler::GetInstance().BroadcastCollisionEvents();
					--accumlatedframes;
				}
			}
		}

		_engineSystems._performanceUsage->PhysicFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		// Audio
		_engineSystems._frameRateControl->StartTimeCounter();

		if (!_engineSystems._imguiSystem->_pause)
		{
			_engineSystems._audioSystem->Update();
		}
		_engineSystems._performanceUsage->AudioFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		// Graphics
		_engineSystems._frameRateControl->StartTimeCounter();

		_engineSystems._graphicsSystem->Update(dt);

		_engineSystems._performanceUsage->GraphicFrameTime = _engineSystems._frameRateControl->EndTimeCounter();

		/*if (EngineSystems::GetInstance()._imguiSystem->_editorMode)
			_engineSystems._physicsSystem->UpdateDraw();
		*/
		// example to draw debug line and circle, to remove later
		/*DebugRenderer::GetInstance().DrawLine(-200, 200, 50, 50);
		DebugRenderer::GetInstance().DrawCircle(50, 50, 50);*/

		_engineSystems._frameRateControl->StartTimeCounter();
		_engineSystems._imguiSystem->Render();  //Renders Imgui Windows - All Imgui windows should be created before this line
		_engineSystems._performanceUsage->IMGUIFrameTime += _engineSystems._frameRateControl->EndTimeCounter();
#else


#endif


		EventHandler::GetInstance().BroadcastObjectEvents();
		::SwapBuffers(_engineSystems._windowSystem->getWindow().get_m_windowDC()); 		// swap double buffer at the end
//-------------------------------------------------------------------------------------------------------------
	}

	_engineSystems._gameObjectFactory->DeleteLevel();
}

int Engine::Exit()
{
	return (int)_engineSystems._windowSystem->Get_msg().wParam;
}
