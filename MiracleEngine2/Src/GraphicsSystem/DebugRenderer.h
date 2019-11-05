#pragma once

#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "QuadMesh.h"
#include "ISingleton.h"

#define NUMBER_OF_VERTICES 16
#define M_PI 3.1415926

class DebugRenderer : public ISingleton<DebugRenderer>
{
public:
	~DebugRenderer();
	DebugRenderer(int windowWidth = 1280/* EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowWidth()*/,
		int windowHeight = 1024 /*EngineSystems::GetInstance()._windowSystem->getWindow().GetWindowHeight() */);
	void Update();
	
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawCircle(float x, float y, float radius);

	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize);

private:
	QuadMesh _quadmesh;
	GLfloat verts[6] = {
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f
	};
	VertexArray* _vao;
	VertexBuffer* _vbo;

	VertexArray* _vaoCircle;
	VertexBuffer* _vboCircle;

	glm::mat4 _proj;  // projection matrix
	Shader _shader{ "Resources/Shader/debug.vert", "Resources/Shader/debug.frag" };

};

#endif

