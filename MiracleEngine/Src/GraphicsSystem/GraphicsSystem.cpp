#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"
#include "PrecompiledHeaders.h"
#include "../Imgui/imgui.h"
#include "InstancedSystem.h"

void GraphicsSystem::Init()
{
	
}


void GraphicsSystem::Update(const TransformComponent* transform, const GraphicComponent* graphic)
{
	ClearScreen();


	//_renderer.DrawPoint(10, -100, 5);
	//_renderer.DrawWireFrameQuad(0, 0, 30, 50);
	
	//_debugrenderer.DrawLine(0, 0, 150, 150);
	if (_renderMode == Instance)
		_instancedRenderer.Update();

	// gl_lines
	// 2 vbo and ebo
	// 1 for square and 1 for lines
	
}


void GraphicsSystem::Exit()
{

}

void GraphicsSystem::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.0f, .0f, .0f, 1.0f);
}