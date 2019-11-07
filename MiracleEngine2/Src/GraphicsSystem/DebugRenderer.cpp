#pragma once

#include "PrecompiledHeaders.h"
#include "DebugRenderer.h"

DebugRenderer::DebugRenderer()
	
{
	_proj = glm::ortho(-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2,
		-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, -15.0f, 15.0f);
	

	_vbo = new VertexBuffer(&verts, 3 * 2 * sizeof(GLfloat));
	_vao = new VertexArray();
	BufferLayout layout;
	layout.Push<float>(3);
	_vao->AddBuffer(*_vbo, layout);



	float radius = 0.5f;
	std::vector<float> vertexBuffer;
	for (float i = 0; i < 2 * M_PI; i += (float)2 * M_PI / NUMBER_OF_VERTICES) {
		vertexBuffer.push_back(cos(i) * radius);    //X coordinate
		vertexBuffer.push_back(sin(i) * radius);    //Y coordinate
		vertexBuffer.push_back(0.0);                //Z coordinate
	}

	_vaoCircle = new VertexArray();
	_vboCircle = new VertexBuffer((void*)vertexBuffer.data(), (unsigned int )vertexBuffer.size() * sizeof(float));
	BufferLayout layout2;
	layout2.Push<float>(3);
	_vaoCircle->AddBuffer(*_vboCircle, layout2);

}

DebugRenderer::~DebugRenderer()
{
	delete _vao;
	delete _vbo;
}
void DebugRenderer::Update()
{

}

void DebugRenderer::DrawCircle(float x, float y, float radiusin)
{
	_vaoCircle->Select();
	_shader.Select();

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 12));
	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(radiusin * 2, radiusin * 2, 0));
	glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * model;
	//glm::mat4 mvp = _proj * trans;
	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	/*glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

	glDrawArrays(GL_LINE_LOOP, 0, NUMBER_OF_VERTICES);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2)
{
	_shader.Select();
	_vao->Select();

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 12));

	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2 - x1, y2 - y1, 0));
	glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * model;



	int location = glGetUniformLocation(_shader._id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader._id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}

void DebugRenderer::DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
{
	_quadmesh.Select();


	_shader.Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 12));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
	glm::mat4 model = translate * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(xsize, ysize, 1.0f));

	glm::mat4 mvp = _proj * model;

	_shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader.SetUniformMat4f("u_MVP", mvp);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// this one encapsulate into another class
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}