#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GraphicsSystem/GraphicsSystem.h"


void Engine::Init()
{
	_graphicSystem = new GraphicsSystem();
}

void Engine::Update()
{


	_graphicSystem->Update();

}

void Engine::Exit()
{
	delete _graphicSystem;
}
