#include "GraphicsSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsSystem/VertexBuffer.h"
#include "PrecompiledHeaders.h"
#include "../Imgui/imgui.h"




void GraphicsSystem::Init()
{

}

void GraphicsSystem::Update(const std::unordered_map < size_t, GraphicComponent* >& graphicmap, 
	 std::unordered_map < size_t, TransformComponent* >& transformmap)	//Cannot Const for transformmap Param -	
																		//Or else cannot use subscript operator for the transformmap
{
	//Example
	//Check for Graphic component first then get Transform COmponent
	for (auto& graphicComponentpair : graphicmap)
	{
		GraphicComponent* graphicComponent = graphicComponentpair.second;
		size_t objID = graphicComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = transformmap[objID]; //Get transform from GameObjectID


		//Whatever graphic rendering for each graphic component of each object.
	}



	//Dont Do the other way - Not check for Transform Comopnent first - GameObject with Transform Component may not have Graphic Component
	//for (auto& transformComponentpair : transformmap)
	//{
	//	TransformComponent * transformComponent = transformComponentpair.second;
	//	size_t objID = transformComponentpair.first;	//Get GameObjectID
	//	GraphicComponent* graphicComponent = graphicmap[objID]; //Get transform from GameObjectID
	//
	//
	//}





	ClearScreen();

	Test();

	// loop through every element in graphic component
	// get texture ID and shader ID
	// get its transform component 
	for (auto const& e : graphicmap)
	{

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