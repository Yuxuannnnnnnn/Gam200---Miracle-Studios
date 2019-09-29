#pragma once

#include "../Engine/GameObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "Shader.h"
#include "VertexArray.h"

class DebugRenderer
{
private:
	GLfloat verts[6] = {
	1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f
	};
	VertexArray* _vao;
	VertexBuffer* _vbo;
	MeshManager _meshmanager;
	glm::mat4 _proj;  // projection matrix
	Shader _shader{ "Src/GraphicsSystem/Shader/debug.vert", "Src/GraphicsSystem/Shader/debug.frag" };
public:
	DebugRenderer(int windowWidth = 800, int windowHeight = 600);
	void Update();
	void DrawLine(float x1, float y1, float x2, float y2);

};