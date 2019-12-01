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

#include "DebugBatchRenderer.h"


#define NUMBER_OF_VERTICES 16
#define M_PI 3.1415926

class DebugRenderer : public ISingleton<DebugRenderer>
{
public:
	~DebugRenderer();
	DebugRenderer();
	void Update();
	
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawCircle(float x, float y, float radius);

	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize);

	void SubmitDebugLine(float x1, float y1, float x2, float y2);
	void BatchDrawDebugLine();
	void CalculateProjMatrix(int windowWidth, int windowHeight);
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
	Shader _batchshader{ "Resources/Shader/batchdebug.vert", "Resources/Shader/batchdebug.frag" };

	DebugBatchRenderer _debugBatchRenderer;
	VertexArray* _vaobatch;
	GLuint _batchvbo;
};

#define DrawDebugLine DebugRenderer::GetInstance().SubmitDebugLine
#define DebugRendererLineDraw DebugRenderer::GetInstance().BatchDrawDebugLine
#define DebugRenderCalculateProjMatrix DebugRenderer::GetInstance().CalculateProjMatrix

#endif

