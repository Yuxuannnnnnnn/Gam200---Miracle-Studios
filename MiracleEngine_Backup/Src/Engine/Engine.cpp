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

#include "GraphicsSystem/GraphicsSystem.h"
 #include <limits>
 typedef std::numeric_limits< double > dbl;


void Engine::Init()
{
	//Creation of the Systems
	_graphicSystem = new GraphicsSystem();
	_frameController = new FrameRateController();
	_inputSystem = new InputSystem();
	_physicSystem = new Physics();
	_inputSystem->Init();
	FrameRateController::GetInstance().Initialize();
	keypressed = false;


	GameObject* newTop =  new GameObject{ Vector3{0,100}, Vector3{100,1} };
	GameObject* newDown = new GameObject{ Vector3{0,-100}, Vector3{100,1} };
	GameObject* newRight = new GameObject{ Vector3{100,0}, Vector3{1,100} };
	GameObject* newLeft = new GameObject{ Vector3{-100,}, Vector3{1,100} };

	Collider2D* topCollider = _physicSystem->CreateEdgeCollider(newTop->_pos, newTop->_scale._x, 0);
	topCollider->_gameObject = newTop;
	Collider2D* downCollider = _physicSystem->CreateEdgeCollider(newDown->_pos, newDown->_scale._x, 0);
	downCollider->_gameObject = newDown;
	Collider2D* rightCollider = _physicSystem->CreateEdgeCollider(newRight->_pos, newRight->_scale._y, PI/2);
	rightCollider->_gameObject = newRight;
	Collider2D* leftCollider = _physicSystem->CreateEdgeCollider(newLeft->_pos, newLeft->_scale._y, PI/2);
	leftCollider->_gameObject = newLeft;

	objList.push_back(newTop);
	objList.push_back(newDown);
	objList.push_back(newRight);
	objList.push_back(newLeft);

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
	//Print out Delta time on the console
	std::cout.precision(dbl::max_digits10);
	double deltaTime = FrameRateController::GetInstance().UpdateFrameTime();

	//std::cout << deltaTime << std::endl;
	//std::cout << _frameController->GetFrameRate() << std::endl;
	ImGui::Text("Engine FPS: %.8f ", FrameRateController::GetInstance().GetFrameRate());

	//Update all the systems
	_graphicSystem->Update();
	_inputSystem->Update();
	_physicSystem->Update(deltaTime);


// keyboard check for different level loading
	// press 0 to delete all GOs
	if (inputsystem->KeyDown(KEYB_0))
	{
		std::vector<GameObject*>::iterator itr = objList.begin();
		while (itr != objList.end())
			delete* itr++;
		objList.resize(0);
	}
	// 1 to load levelText1
	if (inputsystem->KeyDown(KEYB_1))
	{
		std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel.txt");
		objList.insert(objList.end(), temp.begin(), temp.end());
	}
	// 2 to load levelText1
	if (inputsystem->KeyDown(KEYB_2))
	{
		std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel1.txt");
		objList.insert(objList.end(), temp.begin(), temp.end());
	}
	// 3 to load levelText1
	if (inputsystem->KeyDown(KEYB_3))
	{
		std::vector<GameObject*>temp = FileRead_Level("./Resources/TextFiles/TestLevel2.txt");
		objList.insert(objList.end(), temp.begin(), temp.end());
	}

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
}

void Engine::Exit()
{
	std::vector<GameObject*>::iterator itr = objList.begin();
	while (itr != objList.end())
		delete *itr++;


	objFab.erase("Wall");
	objFab.erase("Floor");
	objFab.erase("Player");

	delete _physicSystem;
	delete _graphicSystem;
	delete _inputSystem;
}
