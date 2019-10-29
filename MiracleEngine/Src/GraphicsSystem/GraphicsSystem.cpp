#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"
#include "PrecompiledHeaders.h"
#include "../Imgui/imgui.h"


void GraphicsSystem::Init()
{

}

void GraphicsSystem::Update(const std::unordered_map < size_t, GraphicComponent* >& graphicmap)
{
	ClearScreen();

	Test();

	// loop through every element in graphic component
	// get texture ID and shader ID
	// get its transform component 
	for (auto const& e : graphicmap)
	{
		TransformComponent* tempTrans
			= (TransformComponent*)e.second->GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT);
		tempTrans->GetPos();
		LogicComponent* tempLogic
			= (LogicComponent*)e.second->GetSibilingComponent((unsigned)TypeIdComponent::LOGICCOMPONENT);
		tempLogic->GetHealth();
	}
}


void GraphicsSystem::Exit()
{

}

void GraphicsSystem::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.0f, .0f, .0f, 1.0f);
}


void GraphicsSystem::Test()
{
	_quadmesh.Select();
	_shader.Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0
		, 0, 0));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		glm::vec3(50, 50, 1.0f));

	glm::mat4 mvp = _proj * model;

	_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader.SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}