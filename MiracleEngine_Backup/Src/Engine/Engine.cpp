#pragma once
#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MathLib/Vector3.h"

#include "GraphicsSystem/GraphicsSystem.h"
 #include <limits>
 typedef std::numeric_limits< double > dbl;

void Engine::Init()
{
	//Creation of the Systems
	_graphicSystem = new GraphicsSystem();
	_frameController = new FrameRateController();
	_inputSystem = new InputSystem();

	//Initialisation of Systems
	_inputSystem->Init();
	_frameController->Initialize();

	keypressed = false;

	//Create a new player and adds the player obj to the objlist
	Player* player1 = new Player();
	objList.push_back(player1);
}

void Engine::Update()
{
	//Print out Delta time on the console
	std::cout.precision(dbl::max_digits10);
	double deltaTime = _frameController->UpdateFrameTime();
	//std::cout << deltaTime << std::endl;
	//std::cout << _frameController->GetFrameRate() << std::endl;

	//Update all the systems
	_graphicSystem->Update();
	_inputSystem->Update();


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

	delete _graphicSystem;
	delete _inputSystem;
	delete _frameController;
}
