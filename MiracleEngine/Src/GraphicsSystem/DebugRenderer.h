#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "Shader.h"
#include "VertexArray.h"
#include "QuadMesh.h"
//#include "PhysicSystem/ISingleton.h"

class DebugRenderer //: public ISingleton<DebugRenderer>
{
private:
	QuadMesh _quadmesh;
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
	~DebugRenderer();
	DebugRenderer(int windowWidth = 800, int windowHeight = 600);
	void Update();
	void DrawLine(float x1, float y1, float x2, float y2);

	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize);
};