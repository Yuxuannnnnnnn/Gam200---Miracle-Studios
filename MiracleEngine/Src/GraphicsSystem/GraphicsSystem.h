#pragma once
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"

class GraphicsSystem
{
public:
	void Init();
	void Update();
	void Exit();
private:
	glm::mat4 _proj;
	GLuint _shader;
	MeshManager _meshmanager;
};