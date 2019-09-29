#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"

#include "../Imgui/imgui.h"
#include "InstancedSystem.h"
#include "Engine/FrameRateController.h"



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

	FrameRateController::GetInstance().StartTimeCounter();

	ClearScreen();

	
	//_instancedRenderer.Update();
	//_renderer.DrawPoint(10, -100, 5);
	//_renderer.DrawWireFrameQuad(0, 0, 30, 50);
	_debugrenderer.DrawLine(0, 0, 150,150);
	_renderer.Update();
	// gl_lines
	// 2 vbo and ebo
	// 1 for square and 1 for lines


	//float percentage = (FrameTime / (FrameRateController::GetInstance().GetFrameTimeMS()) * 100.0f);
	//
	//ImGui::Text("Graphics per Frame Percentage: %.3f %", percentage);

	float time = FrameRateController::GetInstance().EndTimeCounter() / FrameRateController::GetInstance().GetFrameTime() * 100;
	ImGui::Text("Graphic per Frame Percentage: %.3f %", time);
}


void GraphicsSystem::Exit()
{

}

void GraphicsSystem::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.0f, .0f, .0f, 1.0f);
}