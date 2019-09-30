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


void GraphicsSystem::Update(double dt)
{

	// Recalculate the current time the frame's been running.
	FrameRateController::GetInstance().StartTimeCounter();

	ClearScreen();

	
	//_renderer.DrawPoint(10, -100, 5);
	//_renderer.DrawWireFrameQuad(0, 0, 30, 50);
	_renderer.Update(dt);
	_debugrenderer.DrawLine(0, 0, 150, 150);
	_instancedRenderer.Update();
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