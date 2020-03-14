#include "PrecompiledHeaders.h"

// BRANDON::testing sol & lua
#include "SystemLogic/ScriptSystem/ScriptSystem.h"

Engine::Engine(HINSTANCE hInstance, int nCmdShow)
{
	_engineSystems.Init(hInstance, nCmdShow);

	MyComponentManger.RegisterAllComponent();
	MyLogicSystem.RegisterAllScript();
}


void Engine::Init()
{
	MyEventHandler.ChangedWindowSize();

	MyFactory.Init();

	MyLogicSystem.bUseOldScripting = true; // set TRUE to use C++ scripting
	MyLogicSystem.Init();

	_engineSystems._scriptSystem->Create_Scripts(); // fill up _ScriptsAll
	_engineSystems._scriptSystem->Init();

	MyInputSystem.Init();

#ifdef LEVELEDITOR
	MyImguiSystem.Init();
	DebugRenderer::GetInstance().Init();
	MyFactory.ChangeScene("SchoolSplashScreen");
#else
	MyFactory.ChangeScene(MyFactory.SerialiseScenes(Serialiser("./Resources/TextFiles/Scenes/GameScenes/GameScenes.json")));
#endif
}


void Engine::Update()
{
	while (MyFactory.GetCurrentScene().compare("Quit"))	//GameState Logic Starts here
	{
		MyFactory.UpdateScene();
		MyEventHandler.BroadcastWindowEvents();

		double dt = MyFrameRateController.UpdateFrameTime();
		double fixedDt = MyFrameRateController.GetLockedDt();
		int accumlatedframes = MyFrameRateController.GetSteps();

		if (!MyWindowsSystem.Update()) //Update the window Object - reads all messages received in this window objects
			return;

#ifdef LEVELEDITOR
		MyPerformanceUsage.PerFrameTime = MyFrameRateController.GetFrameTime();
		MyPerformanceUsage.FPS = MyFrameRateController.GetFPS();

		MyFrameRateController.StartTimeCounter();
		MyImguiSystem.UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update
		MyPerformanceUsage.IMGUIFrameTime += MyFrameRateController.EndTimeCounter();

		MyFrameRateController.StartTimeCounter();
		MyInputSystem.Update(MyWindowsSystem.getWindow());
		MyCameraSystem.Update();
		MyPerformanceUsage.InputFrameTime += MyFrameRateController.EndTimeCounter();


		if (!MyImguiSystem._editorMode)
		{
			ShowCursor(false);

			if (!MyInputSystem._pause)
			{

				if (fixedDt)
				{
					if (accumlatedframes)
					{
						while (accumlatedframes)
						{
							MyFrameRateController.StartTimeCounter();
							MyLogicSystem.Update(fixedDt);
							MyAiSystem.Update(fixedDt);
							MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();

							MyFrameRateController.StartTimeCounter();
							MyPhysicsSystem.Update(fixedDt);
							MyEventHandler.BroadcastCollisionEvents();
							MyPerformanceUsage.PhysicFrameTime += MyFrameRateController.EndTimeCounter();

							--accumlatedframes;
						}
					}
					else
					{
						MyFrameRateController.StartTimeCounter();
						MyLogicSystem.Update(0.0);
						MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();
					}
				}
				else
				{
					MyFrameRateController.StartTimeCounter();
					MyLogicSystem.Update(dt);
					MyAiSystem.Update(dt);
					MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();

					MyFrameRateController.StartTimeCounter();
					MyPhysicsSystem.Update(dt);
					MyEventHandler.BroadcastCollisionEvents();
					MyPerformanceUsage.PhysicFrameTime += MyFrameRateController.EndTimeCounter();
				}
			}
			else
			{
				MyFrameRateController.StartTimeCounter();
				MyLogicSystem.Update(-10.0);
				MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();

				
			}

			MyFrameRateController.StartTimeCounter();
			MyAudioSystem.Update();
			MyPerformanceUsage.AudioFrameTime += MyFrameRateController.EndTimeCounter();
		}

		MyFrameRateController.StartTimeCounter();

		if (!MyInputSystem._pause)
			MyAnimationSystem.Update(dt);

		if (!MyInputSystem._pause)
			MyGraphicsSystem.Update(dt);
		else
			MyGraphicsSystem.Update(-10.0);

		if (!MyInputSystem._pause)
			MyAnimationSystem.UpdatePlayOnce();

		MyPhysicsSystem.Draw();
		MyPerformanceUsage.GraphicFrameTime += MyFrameRateController.EndTimeCounter();

		MyFrameRateController.StartTimeCounter();
		if (MyImguiSystem._editorMode && !MyInspectionWindow.GetTileMapEditor())
		{
			MyImGuizmoManager.Update();
		}
		
		MyImguiSystem.Render();  //Renders Imgui Windows - All Imgui windows should be created before this line
		MyPerformanceUsage.IMGUIFrameTime += MyFrameRateController.EndTimeCounter();
#else
		MyInputSystem.Update(MyWindowsSystem.getWindow());
		MyCameraSystem.Update();

		if (!MyInputSystem._pause)
		{
			if (fixedDt)
			{
				if (accumlatedframes)
				{
					while (accumlatedframes)
					{
						MyLogicSystem.Update(fixedDt);
						MyAiSystem.Update(fixedDt);
							
						MyPhysicsSystem.Update(fixedDt);
						MyEventHandler.BroadcastCollisionEvents();
						
						--accumlatedframes;
					}
				}
				else
					MyLogicSystem.Update(0.0);
			}
			else
			{
				MyLogicSystem.Update(dt);
				MyAiSystem.Update(dt);
					
				MyPhysicsSystem.Update(dt);
				MyEventHandler.BroadcastCollisionEvents();
			}
		}
		else
			MyLogicSystem.Update(-10.0);

		MyAudioSystem.Update();

		if (!MyInputSystem._pause)
			MyAnimationSystem.Update(dt);

		if (!MyInputSystem._pause)
			MyGraphicsSystem.Update(dt);
		else
			MyGraphicsSystem.Update(-10.0);

		if (!MyInputSystem._pause)
			MyAnimationSystem.UpdatePlayOnce();
#endif

		MyFactory.Update(dt);
		::SwapBuffers(MyWindowsSystem.getWindow().get_m_windowDC()); 		// swap double buffer at the end
//-------------------------------------------------------------------------------------------------------------
	}

	MyFactory.ClearLevel();
}

int Engine::Exit()
{
	return (int)MyWindowsSystem.Get_msg().wParam;
}
