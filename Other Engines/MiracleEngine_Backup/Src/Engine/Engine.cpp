#pragma once

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "../Imgui/imgui_internal.h"

#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MathLib/SYMath.h"
#include "PhysicSystem/Coin.h"

#include "GraphicsSystem/GraphicsSystem.h"
#include <limits>
typedef std::numeric_limits< double > dbl;


void Engine::Init()
{
	_physicSystem = new Physics();

	for (int i = 0; i < 39; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			GameObject* newGO = new GameObject{ {(float)((i - 20) * 15), float((j - 20) * 15) }, {5,5} };

			RigidBody2D* newBody = _physicSystem->CreateRigidBody2D();
			newBody->_gameObject = newGO;
			newBody->_velocity = Vector3{ 10.f,10.f,0 };
			newBody->_static = true;

			objStressTestList.push_back(newGO);
		}
	}

	//Creation of the Systems
	_graphicSystem = new GraphicsSystem();
	_inputSystem = new InputSystem();
	_inputSystem->Init();
	_fController = new FrameRateController();
	_fController->Initialize();
	_pUsage = new PerformanceUsage();
	keypressed = false;

	// get Fabs
	Player* temp = new Player();
	temp->Serialize();
	objFab.insert(std::pair<std::string, GameObject*>("Wall", new Wall()));
	objFab.insert(std::pair<std::string, GameObject*>("Floor", new Floor()));
	objFab.insert(std::pair<std::string, GameObject*>("Player", temp));

	// instantiate world from LevelTest.txt
	//objList = FileRead_Level("./Resources/TextFiles/TestLevel.txt");
}

void Engine::Update()
{
	_pUsage->PrintPerformanceUsage();

	//Print out Delta time on the console
	std::cout.precision(dbl::max_digits10);
	double deltaTime = _fController->UpdateFrameTime();

	_pUsage->PerFrameTime = _fController->GetFrameTime();
	_pUsage->FPS = _fController->GetFPS();
	_pUsage->FrameRate = _fController->GetFrameRate();

	//Update all the systems
	_fController->StartTimeCounter();
	_graphicSystem->Update(deltaTime);
	_pUsage->GraphicFrameTime = _fController->EndTimeCounter();

	_fController->StartTimeCounter();
	_inputSystem->Update();
	_pUsage->InputFrameTime = _fController->EndTimeCounter();

	_fController->StartTimeCounter();
	_physicSystem->Update(deltaTime);
	_pUsage->PhysicFrameTime = _fController->EndTimeCounter();

	// keyboard check for different level loading
		// press 0 to delete all GOs
	if (inputsystem->KeyDown(KEYB_0))
	{
		if (!keypressed)
		{
			std::vector<GameObject*>::iterator itr = objList.begin();
			while (itr != objList.end())
				delete* itr++;
			objList.resize(0);
			_physicSystem->Clear();

			keypressed = true;
		}
	}
	// 1 to load levelText1
	else if (inputsystem->KeyDown(KEYB_1))
	{
		if (!keypressed)
		{
			std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel.txt");
			objList.insert(objList.end(), temp.begin(), temp.end());
			keypressed = true;
		}
	}
	// 2 to load levelText1
	else if (inputsystem->KeyDown(KEYB_2))
	{
		if (!keypressed)
		{
			std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel1.txt");
			objList.insert(objList.end(), temp.begin(), temp.end());
			keypressed = true;
		}
	}
	// 3 to load levelText1
	else if (inputsystem->KeyDown(KEYB_3))
	{
		if (!keypressed)
		{
			std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel2.txt");
			objList.insert(objList.end(), temp.begin(), temp.end());
			keypressed = true;
		}
	}
	// create walls
	else if (inputsystem->KeyDown(KEYB_4))
	{
		if (!keypressed)
		{
			_physicSystem->Clear();

			Collider2D* topCollider = _physicSystem->CreateEdgeCollider(Vector3{ 0,200 }, 400, 0);
			Collider2D* downCollider = _physicSystem->CreateEdgeCollider(Vector3{ 0,-200 }, 400, 0);
			Collider2D* rightCollider = _physicSystem->CreateEdgeCollider(Vector3{ 200,0 }, 400, PI / 2);
			Collider2D* leftCollider = _physicSystem->CreateEdgeCollider(Vector3{ -200, }, 400, PI / 2);

			keypressed = true;
		}
	}
	else if (inputsystem->KeyDown(KEYB_5))
	{
		if (!keypressed)
		{
			//_physicSystem->Clear();

			GameObject* ball = new GameObject(Vector3{ 0,0,0 }, Vector3{ 30,30,0 });

			RigidBody2D* ballBody = _physicSystem->CreateRigidBody2D();
			ballBody->_gameObject = ball;
			ballBody->_velocity = Vector3{ 200,80,0 };
			ballBody->_static = false;

			Collider2D* ballCollider = _physicSystem->CreateCircleCollider(ball->_pos, ball->_scale._x / 2);
			ballCollider->_gameObject = ball;
			ballCollider->_body = ballBody;

			objList.push_back(ball);

			keypressed = true;
		}
	}
	else if (inputsystem->KeyDown(KEYB_6))
	{
		if (!keypressed)
		{
			//_physicSystem->Clear();

			GameObject* coin = new Coin();
			coin->_pos = Vector3{ 100,100,0 };
			coin->_scale = Vector3{ 40,40,0 };

			Collider2D* coinCollider = _physicSystem->CreateBoxCollider(coin->_pos, coin->_scale, 0);
			coinCollider->_gameObject = coin;

			objList.push_back(coin);

			keypressed = true;
		}
	}
	else if (inputsystem->KeyDown(KEYB_M))
	{
		if (!keypressed)
		{
			_graphicSystem->_renderMode = None;
		}
	}
	else if (inputsystem->KeyDown(KEYB_N))
	{
		if (!keypressed)
		{
			_graphicSystem->_renderMode = Instance;
		}
	}
	else if (inputsystem->KeyDown(KEYB_B))
	{
		if (!keypressed)
		{
			_graphicSystem->num = 0;
		}
	}
	else if (inputsystem->KeyDown(KEYB_V))
	{
		if (!keypressed)
		{
			_graphicSystem->num = 1;
		}
	}
	else if (inputsystem->KeyDown(KEYB_C))
	{
		if (!keypressed)
		{
			_graphicSystem->num = 2;
		}
	}
	else if (inputsystem->KeyDown(KEYB_X))
	{
		if (!keypressed)
		{
			_graphicSystem->_renderMode = Font;
		}
	}
	else
		keypressed = false;

	_fController->StartTimeCounter();

	// Update for all current game objects
	std::vector<GameObject*>::iterator itr = objList.begin();
	while (itr != objList.end())
	{
		GameObject* temp = *itr;
		Player* tempP = dynamic_cast<Player*>(temp);
		if (tempP)
			tempP->Update();
		itr++;
	}

	_pUsage->LogicFrameTime = _fController->EndTimeCounter();
}

void Engine::Exit()
{
	std::vector<GameObject*>::iterator itr = objList.begin();
	while (itr != objList.end())
		delete* itr++;


	objFab.erase("Wall");
	objFab.erase("Floor");
	objFab.erase("Player");

	delete _fController;
	delete _pUsage;
	delete _physicSystem;
	delete _graphicSystem;
	delete _inputSystem;
}
