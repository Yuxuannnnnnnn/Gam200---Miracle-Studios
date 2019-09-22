#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GraphicsSystem/GraphicsSystem.h"


void Engine::Init()
{
	_graphicsSystem->Init();
	_gameObjectFactory->CreateGameObject(PLAYER);

}

void Engine::Update()
{
	_graphicsSystem->Update();
}

void Engine::Exit()
{
	delete _graphicsSystem;

	//delete all objects in the gameObjectFactory
	delete _gameObjectFactory;
}