#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"

#include "../Imgui/imgui.h"
#include "InstancedSystem.h"



void GraphicsSystem::Init()
{
	
}


void GraphicsSystem::Update()
{
	//VertexBuffer vb((const void*)positions, sizeof(glm::vec2) * 3);

	////each function call: create layout for each vertex attribute
	////1. index of attribute of vertex
	////2. number of floats for the attribute
	////3. type of data
	////4. To normalise or not
	////5. Size(bytes) of Stride from vertex to vertex
	////6. offset of number of bytes in a vertex to get to the attribute
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const void*)0);

	////enable the index of the vertex attribute
	//glEnableVertexAttribArray(0);

	// Recalculate the current time the frame's been running.

	PrevTime = Time::now();


	ClearScreen();

	
	//_instancedRenderer.Update();
	//_renderer.DrawPoint(10, -100, 5);
	//_renderer.DrawWireFrameQuad(0, 0, 30, 50);
	_debugrenderer.DrawLine(0, 0, 150,150);
	_renderer.Update();
	// gl_lines
	// 2 vbo and ebo
	// 1 for square and 1 for lines

	CurrTime = Time::now();

	FrameTime = std::chrono::duration_cast<ms>(CurrTime - PrevTime);

	ImGui::Text("Graphics FPS: %.8f ", (FrameTime/FrameRateController::GetFrameRate() * 100));
}
void GraphicsSystem::Exit()
{

}

void GraphicsSystem::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.0f, .0f, .0f, 1.0f);
}