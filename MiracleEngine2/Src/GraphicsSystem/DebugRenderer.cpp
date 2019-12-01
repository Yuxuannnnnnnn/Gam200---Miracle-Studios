#pragma once

#include "PrecompiledHeaders.h"
#include "DebugRenderer.h"

DebugRenderer::DebugRenderer()
{
	std::string temp = "DefaultDebugShader";

	_shader = ResourceManager::GetInstance().GetShaderResource(temp);

	if (!_shader && ResourceManager::GetInstance().AddNewShaderResource({ temp,{ "Resources/Shader/debug.vert", "Resources/Shader/debug.frag" } }))
	{
		_shader = ResourceManager::GetInstance().GetShaderResource(temp);
	}

	temp = "DefaultBatchShader";

	_batchshader = ResourceManager::GetInstance().GetShaderResource(temp);

	if (!_batchshader && ResourceManager::GetInstance().AddNewShaderResource({ temp,{ "Resources/Shader/batchdebug.vert", "Resources/Shader/batchdebug.frag" } }))
	{
		_batchshader = ResourceManager::GetInstance().GetShaderResource(temp);
	}

	_proj = glm::ortho(-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2,
		-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, -15.0f, 15.0f);

	_vaobatch = new VertexArray();
	glGenBuffers(1, &_batchvbo);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	_vao = new VertexArray();
	_vbo = new VertexBuffer(&verts, 3 * 2 * sizeof(GLfloat));
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
	_vboCircle = new VertexBuffer((void*)vertexBuffer.data(), (unsigned int)vertexBuffer.size() * sizeof(float));
	BufferLayout layout2;
	layout2.Push<float>(3);
	_vaoCircle->AddBuffer(*_vboCircle, layout2);
}

DebugRenderer::~DebugRenderer()
{
	delete _vao;
	delete _vbo;
	delete _vaoCircle;
	delete _vboCircle;
	delete _vaobatch;
}
void DebugRenderer::Update()
{

}

void DebugRenderer::DrawCircle(float x, float y, float radiusin)
{
	_vaoCircle->Select();
	_shader->Select();

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 12));
	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(radiusin * 2, radiusin * 2, 0));
	glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * model;
	//glm::mat4 mvp = _proj * trans;
	int location = glGetUniformLocation(_shader->_id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader->_id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	/*glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

	glDrawArrays(GL_LINE_LOOP, 0, NUMBER_OF_VERTICES);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2)
{
	_shader->Select();
	_vao->Select();

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 12));

	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2 - x1, y2 - y1, 0));
	glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * model;



	int location = glGetUniformLocation(_shader->_id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader->_id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}



void DebugRenderer::SubmitDebugLine(float x1, float y1, float x2, float y2)
{
	/*
	GLfloat verts[6] = {
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f
	};
	*/

	// initial vertex application side
	glm::vec4 vertex1{ x1, y1, 14, 0 };
	glm::vec4 vertex2{ x2, y2, 14, 0 };

	static float angle = 0.0f;

	// calculate MVP
	//glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 12));
	//glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2 - x1, y2 - y1, 0)) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
	angle += 0.01f;
	//glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix();


	// apply MVP to vertex
	//glm::vec4 vertex1 = mvp * vertex01;
	//glm::vec4 vertex2 = mvp * vertex02;

	_debugBatchRenderer.vert.push_back(vertex1.x);
	_debugBatchRenderer.vert.push_back(vertex1.y);
	_debugBatchRenderer.vert.push_back(vertex1.z);

	_debugBatchRenderer.vert.push_back(vertex2.x);
	_debugBatchRenderer.vert.push_back(vertex2.y);
	_debugBatchRenderer.vert.push_back(vertex2.z);
}

void DebugRenderer::BatchDrawDebugLine()
{
	if (_debugBatchRenderer.vert.empty())
		return;

	_vaobatch->Select();

	// select batch shader
	_shader->Select();


	// bind buffer in batch renderer
	glBindBuffer(GL_ARRAY_BUFFER, _batchvbo);
	glBufferData(GL_ARRAY_BUFFER, _debugBatchRenderer.vert.size() * 4, &_debugBatchRenderer.vert[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	

	glm::mat4 view = EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix();
	glm::mat4 mvp = _proj * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix();
	
	int location = glGetUniformLocation(_batchshader->_id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader->_id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_LINES, 0, _debugBatchRenderer.vert.size() / 3);

	// clear buffer every loop
	_debugBatchRenderer.vert.clear();
}



void DebugRenderer::DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
{
	_quadmesh.Select();


	_shader->Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 12));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
	glm::mat4 model = translate * EngineSystems::GetInstance()._graphicsSystem->GetCamera().GetCamMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(xsize, ysize, 1.0f));

	glm::mat4 mvp = _proj * model;

	_shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader->SetUniformMat4f("u_MVP", mvp);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// this one encapsulate into another class
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}