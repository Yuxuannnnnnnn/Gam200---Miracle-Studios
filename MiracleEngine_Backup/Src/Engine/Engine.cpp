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
}

void Engine::Update()
{
	std::cout.precision(dbl::max_digits10);
	double deltaTime = _frameController->UpdateFrameTime();
	//std::cout << deltaTime << std::endl;
	//std::cout << _frameController->GetFrameRate() << std::endl;

	_graphicSystem->Update();
	_inputSystem->Update();

	if (_inputSystem->KeyDown(KEYB_A))
	{
		std::cout << "A pressed !" << std::endl;
	}
}

void Engine::Exit()
{
	delete _graphicSystem;
}
