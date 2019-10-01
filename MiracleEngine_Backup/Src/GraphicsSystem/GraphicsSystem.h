#pragma once
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "../Engine/GameObject.h"
#include <string>
#include "GraphicsSystem/RendererSystem.h"
#include "VertexArray.h"

#include "InstancedSystem.h"
#include "DebugRenderer.h"
enum RenderMode
{
	None,
	Instance
};
class GraphicsSystem
{
public:
	void Init();
	void Update(double dt);
	void Exit();
	RenderMode _renderMode = None;
	int num = 0;
private:
	void ClearScreen() const;
	glm::mat4 _proj;
	GLuint _shader;
	MeshManager _meshmanager;
	RendererSystem _renderer;
	InstancedSystem _instancedRenderer;
	DebugRenderer _debugrenderer;
	
};