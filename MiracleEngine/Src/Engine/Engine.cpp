#include "PrecompiledHeaders.h"

// BRANDON::testing sol & lua
#include "SystemLogic/ScriptSystem/ScriptSystem.h"

void Engine::Init()
{
	RegisterComponent(Identity);
	RegisterComponent(Transform);
	RegisterComponent(Graphic);
	RegisterComponent(Animation);
	RegisterComponent(Camera);
	RegisterComponent(Font);
	RegisterComponent(RigidBody2D);
	RegisterComponent(CircleCollider2D);
	RegisterComponent(BoxCollider2D);
	RegisterComponent(EdgeCollider2D);
	RegisterComponent(Logic);
	RegisterComponent(Audio);
	RegisterComponent(Button);
	RegisterComponent(TileMap);

	MyImguiSystem.Init();
#ifndef LEVELEDITOR

	MySceneManager.SerialiseScenes(Serialiser("./Resources/TextFiles/Scenes/GameScenes/GameScenes.json"));
#endif
	_engineSystems._inputSystem->Init();
	_engineSystems._scriptSystem->Init();


//-------------------------------------------------------------
}


void Engine::Update()
{
	bool test = true; // BRANDON::testing sol & lua
	if (test)
	{
		_engineSystems._scriptSystem->testfunc();
		_engineSystems._scriptSystem->Test_BasicFuncitonality();
		_engineSystems._scriptSystem->Test_DataCompEditing();
	}

	MyFactory.ChangeScene("Level1");

	while (MyFactory.GetCurrentScene().compare("Quit"))	//GameState Logic Starts here
	{

		double dt = MyFrameRateController.UpdateFrameTime();
		double fixedDt = MyFrameRateController.GetLockedDt();
		int accumlatedframes = MyFrameRateController.GetSteps();

		//_gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");
			//------Systems update here----- Please do not change the Order of the Systems Update--------------------------

		if (!MyWindowsSystem.Update()) //Update the window Object - reads all messages received in this window objects
		{
			//_gameStateManager->SetNextGameState(GameStateId::GS_QUIT); 
			return;
		}

#ifdef LEVELEDITOR

		MyPerformanceUsage.PerFrameTime = MyFrameRateController.GetFrameTime();
		MyPerformanceUsage.FPS = MyFrameRateController.GetFPS();

		MyFrameRateController.StartTimeCounter();
		MyImguiSystem.UpdateFrame();  //ImguiSystem updateframe must be before GraphicsSystem update, graphicSystem to clear buffer after each frame update
		MyPerformanceUsage.IMGUIFrameTime += MyFrameRateController.EndTimeCounter();


		MyFrameRateController.StartTimeCounter();
		MyInputSystem.Update(MyWindowsSystem.getWindow());
		MyPerformanceUsage.InputFrameTime += MyFrameRateController.EndTimeCounter();


		MyFrameRateController.StartTimeCounter();
		if (!MyImguiSystem._editorMode)
		{
			//MyButtonManager.Update();
			MyEventHandler.BroadcastInputEvents();
			MyPerformanceUsage.PhysicFrameTime += MyFrameRateController.EndTimeCounter();
		}
		else
		{
			MyImGuizmoManager.Update();
			MyPerformanceUsage.IMGUIFrameTime += MyFrameRateController.EndTimeCounter();
		}


		if (!MyImguiSystem._editorMode)
		{
			if (fixedDt)
			{
				while (accumlatedframes)
				{
					// Logic
					MyFrameRateController.StartTimeCounter();
					MyLogicSystem.Update(fixedDt);
					MyAiSystem.Update(fixedDt);
					MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();

					//physics
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
				MyLogicSystem.Update(dt);
				MyAiSystem.Update(dt);
				MyPerformanceUsage.LogicFrameTime += MyFrameRateController.EndTimeCounter();

				//physics
				MyFrameRateController.StartTimeCounter();
				MyPhysicsSystem.Update(dt);
				MyEventHandler.BroadcastCollisionEvents();
				MyPerformanceUsage.PhysicFrameTime += MyFrameRateController.EndTimeCounter();
			}

			// Audio
			MyFrameRateController.StartTimeCounter();
			MyAudioSystem.Update();
			MyPerformanceUsage.AudioFrameTime += MyFrameRateController.EndTimeCounter();
		}

		// Graphics
		MyFrameRateController.StartTimeCounter();
		MyAnimationSystem.Update(dt);
		MyGraphicsSystem.Update(dt);
		MyPerformanceUsage.GraphicFrameTime += MyFrameRateController.EndTimeCounter();

		MyFrameRateController.StartTimeCounter();
		MyImguiSystem.Render();  //Renders Imgui Windows - All Imgui windows should be created before this line

#else
		MyInputSystem.Update(MyWindowsSystem.getWindow());

		//MyButtonManager.Update();
		MyEventHandler.BroadcastInputEvents();
	
		if (fixedDt)
		{
			while (accumlatedframes)
			{
				// Logic
				MyLogicSystem.Update(fixedDt);
				MyAiSystem.Update(fixedDt);

				//physics
				MyPhysicsSystem.Update(fixedDt);
				MyEventHandler.BroadcastCollisionEvents();

				--accumlatedframes;
			}
		}
		else
		{
			MyLogicSystem.Update(dt);
			MyAiSystem.Update(dt);

			//physics
			MyPhysicsSystem.Update(dt);
			MyEventHandler.BroadcastCollisionEvents();
		}

		// Audio
		MyAudioSystem.Update();
			
		// Graphics
		MyAnimationSystem.Update(dt);
		MyGraphicsSystem.Update(dt);
#endif

		MyEventHandler.BroadcastObjectEvents();
		MyFactory.Update(dt);
		::SwapBuffers(MyWindowsSystem.getWindow().get_m_windowDC()); 		// swap double buffer at the end
//-------------------------------------------------------------------------------------------------------------
	}

	MyFactory.DeleteLevel();
}

int Engine::Exit()
{
	return (int)MyWindowsSystem.Get_msg().wParam;
}
