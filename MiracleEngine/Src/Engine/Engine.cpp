#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#include "GraphicsSystem/GraphicsSystem.h"


void Engine::Init()
{
	_graphicSystem = new GraphicsSystem();
	_frameController = new FrameRateController();

	_frameController->Initialize();
}

void Engine::Update()
{
	
	double deltaTime = _frameController->UpdateFrameTime();
	(void)deltaTime;


	_graphicSystem->Update();

}

void Engine::Exit()
{
	delete _graphicSystem;
	delete _frameController;
}
