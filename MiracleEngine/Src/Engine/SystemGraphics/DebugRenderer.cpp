#pragma once

#include "PrecompiledHeaders.h"
#include "DebugRenderer.h"

void DebugRenderer::CalculateProjMatrix(int windowWidth, int windowHeight)
{
	_proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2, -150.0f, 150.0f);

}
DebugRenderer::DebugRenderer()
{
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

void DebugRenderer::Init()
{
	std::string temp = "DefaultDebugShader";

	_shader = MyResourceSystem.GetShaderResource(temp);

	if (!_shader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/debugSystem.vert", "Resources/Shader/debugSystem.frag" } }))
	{
		_shader = MyResourceSystem.GetShaderResource(temp);
	}

	temp = "DefaultBatchShader";

	_batchshader = MyResourceSystem.GetShaderResource(temp);

	if (!_batchshader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/batchdebug.vert", "Resources/Shader/batchdebug.frag" } }))
	{
		_batchshader = MyResourceSystem.GetShaderResource(temp);
	}

	_proj = glm::ortho(-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth() / 2,
		-(float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, (float)EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() / 2, -150.0f, 150.0f);
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
	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m) * model;
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
	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m) * model;



	int location = glGetUniformLocation(_shader->_id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader->_id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}



void DebugRenderer::SubmitDebugLine(glm::vec3 p1, glm::vec3 p2)
{
	SubmitDebugLine(p1.x, p1.y, p2.x, p2.y);
}

void DebugRenderer::SubmitDebugLine(float x1, float y1, float x2, float y2)
{

	//GLfloat verts[6] = {
	//1.0f, 1.0f, 0.0f,
	//0.0f, 0.0f, 0.0f
	//};
	//

	// initial vertex application side
	glm::vec4 vertex1{ x1, y1, 14, 0 };
	glm::vec4 vertex2{ x2, y2, 14, 0 };


	//calculate MVP
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 12));

	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2 - x1, y2 - y1, 0));

	/*vertex1 = model * vertex1;
	vertex2 = model * vertex2;*/
	/*glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x1, y1, 10));
	glm::mat4 model = trans * glm::scale(glm::mat4(1.0f), glm::vec3(x2 - x1, y2 - y1, 0)) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m) * model;*/

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



	glm::mat4 view = glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m);
	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m);

	int location = glGetUniformLocation(_batchshader->_id, "u_Color");
	glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);

	location = glGetUniformLocation(_shader->_id, "u_MVP");
	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	auto size = _debugBatchRenderer.vert.size() / 3;

	glDrawArrays(GL_LINES, 0, (GLsizei)size);


	// clear buffer every loop
	_debugBatchRenderer.vert.clear();
}



void DebugRenderer::DrawBox(const glm::vec3& center, const glm::vec3& scale)
{
	glm::vec3 topleft;
	glm::vec3 topright;
	glm::vec3 botleft;
	glm::vec3 botright;

	topleft.x = (center.x - scale.x) / 2;
	topleft.y = (center.y + scale.y) / 2;

	topright.x = (center.x + scale.x) / 2;
	topright.y = (center.y + scale.y) / 2;

	botleft.x = (center.x - scale.x) / 2;
	botleft.y = (center.y - scale.y) / 2;

	botright.x = (center.x + scale.x) / 2;
	botright.y = (center.y - scale.y) / 2;
	SubmitDebugLine(topleft, topright);
	SubmitDebugLine(topleft, botleft);
	SubmitDebugLine(topright, botright);
	SubmitDebugLine(botleft, botright);
}

void DebugRenderer::DrawBox(const glm::vec3& topleft, const glm::vec3& topright, const glm::vec3& botleft, const glm::vec3& botright)
{
	SubmitDebugLine(topleft, topright);
	SubmitDebugLine(topleft, botleft);
	SubmitDebugLine(topright, botright);
	SubmitDebugLine(botleft, botright);
}

void DebugRenderer::DrawBox(const glm::vec3& botleft, const glm::vec3& topright, bool aabb)
{
	aabb;
	glm::vec3 topleft;
	glm::vec3 botright;

	topleft.x = botleft.x;
	topleft.y = topright.y;

	botright.x = topright.x;
	botright.y = botleft.y;

	SubmitDebugLine(topleft, topright);
	SubmitDebugLine(topleft, botleft);
	SubmitDebugLine(topright, botright);
	SubmitDebugLine(botleft, botright);
}


void DebugRenderer::FillBox(const glm::vec3& center, const glm::vec3& scale)
{
	_quadmesh.Select();
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), center);
	//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		scale);

	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m) * model;

	_shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 0.2f);

	_shader->SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DebugRenderer::FillBox(const glm::vec3& topleft, const glm::vec3& topright, const glm::vec3& botleft, const glm::vec3& botright)
{
	glm::vec3 center;
	center.x = (topright.x - topleft.x) / 2;
	center.y = (topright.y - botleft.y) / 2;
	
	glm::vec3 scale;
	scale.x = topright.x - topleft.x;
	scale.y = topright.y - botleft.y;

	FillBox(center, scale);
}

void DebugRenderer::FillBox(const glm::vec3& botleft, const glm::vec3& topright, bool aabb)
{
	aabb;
	glm::vec3 topleft;
	glm::vec3 botright;

	topleft.x = botleft.x;
	topleft.y = topright.y;

	botright.x = topright.x;
	botright.y = botleft.y;

	glm::vec3 center;
	center.x = (topright.x - topleft.x) / 2;
	center.y = (topright.y - botleft.y) / 2;

	glm::vec3 scale;
	scale.x = topright.x - topleft.x;
	scale.y = topright.y - botleft.y;

	FillBox(center, scale);
}

void DebugRenderer::FillBox(const glm::vec3& center, const glm::vec3& scale, const glm::vec4& color)
{
	_quadmesh.Select();
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), center);
	//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		scale);

	glm::mat4 mvp = _proj * glm::make_mat4(Matrix4x4::CreateTranspose(MyCameraSystem.GetCamMatrix()).m) * model;

	_shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	_shader->SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DebugRenderer::FillBox(const glm::vec3& topleft, const glm::vec3& topright, const glm::vec3& botleft, 
	const glm::vec3& botright, const glm::vec4& color)
{
	glm::vec3 center;
	center.x = (topright.x - topleft.x) / 2;
	center.y = (topright.y - botleft.y) / 2;

	glm::vec3 scale;
	scale.x = topright.x - topleft.x;
	scale.y = topright.y - botleft.y;

	FillBox(center, scale, color);
}

void DebugRenderer::FillBox(const glm::vec3& botleft, const glm::vec3& topright, bool aabb, const glm::vec4& color)
{
	aabb;
	glm::vec3 topleft;
	glm::vec3 botright;

	topleft.x = botleft.x;
	topleft.y = topright.y;

	botright.x = topright.x;
	botright.y = botleft.y;

	glm::vec3 center;
	center.x = (topright.x - topleft.x) / 2;
	center.y = (topright.y - botleft.y) / 2;

	glm::vec3 scale;
	scale.x = topright.x - topleft.x;
	scale.y = topright.y - botleft.y;

	FillBox(center, scale, color);
}

void DebugRenderer::DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize)
{
	_quadmesh.Select();


	_shader->Select();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 12));
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(xsize, ysize, 1.0f));

	glm::mat4 mvp = _proj * model;

	_shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader->SetUniformMat4f("u_MVP", mvp);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// this one encapsulate into another class
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}