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
	glm::vec2 positions[3] = {
		{ -0.5f, -0.5f },
		{ 0.0f, 0.5f   },
		{ 0.5f, -0.5f  }
	};

	VertexBuffer vb((const void* )positions, sizeof(glm::vec2) * 3);

	//each function call: create layout for each vertex attribute
	//1. index of attribute of vertex
	//2. number of floats for the attribute
	//3. type of data
	//4. To normalise or not
	//5. Size(bytes) of Stride from vertex to vertex
	//6. offset of number of bytes in a vertex to get to the attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const void *)0);

	//enable the index of the vertex attribute
	glEnableVertexAttribArray(0);

	_graphicSystem->Update();

}

void Engine::Exit()
{
	delete _graphicSystem;
}
