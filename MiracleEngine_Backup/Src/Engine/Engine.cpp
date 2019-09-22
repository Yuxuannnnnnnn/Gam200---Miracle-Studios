#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GraphicsSystem/GraphicsSystem.h"
 #include <limits>
 typedef std::numeric_limits< double > dbl;

void Engine::Init()
{
	_graphicSystem = new GraphicsSystem();
	_frameController = new FrameRateController();
	_inputSystem = new InputSystem();
	_inputSystem->Init();
	_frameController->Initialize();
	keypressed = false;
}

void Engine::Update()
{
	std::cout.precision(dbl::max_digits10);
	double deltaTime = _frameController->UpdateFrameTime();
	//std::cout << deltaTime << std::endl;
	//std::cout << _frameController->GetFrameRate() << std::endl;

	_graphicSystem->Update();
	_inputSystem->Update();

	if (_inputSystem->KeyDown(KEYB_A) && !keypressed)
	{
		// testing gameobject, delete later
		objList.push_back(GameObject{ Vec3{100,50}, Vec3{50,50} });
		std::cout << "A pressed !" << std::endl;

		keypressed = true;
	}
	else if (!_inputSystem->KeyDown(KEYB_A) && keypressed)
	{
		keypressed = false;
	}

	if (_inputSystem->KeyDown(KEYB_B) && !keypressed)
	{
		// testing gameobject, delete later
		objList.push_back(GameObject{ Vec3{100,-50}, Vec3{50,50} });
		std::cout << "A pressed !" << std::endl;

		keypressed = true;
	}
	else if (!_inputSystem->KeyDown(KEYB_B) && keypressed)
	{
		keypressed = false;
	}

	if (_inputSystem->KeyDown(KEYB_C) && !keypressed)
	{
		// testing gameobject, delete later
		objList.push_back(GameObject{ Vec3{-100,50}, Vec3{50,50} });
		std::cout << "A pressed !" << std::endl;

		keypressed = true;
	}
	else if (!_inputSystem->KeyDown(KEYB_C) && keypressed)
	{
		keypressed = false;
	}
}

void Engine::Exit()
{
	delete _graphicSystem;
}
