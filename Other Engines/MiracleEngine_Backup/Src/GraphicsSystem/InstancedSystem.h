#pragma once
#include "../Engine/GameObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "Shader.h"
#include "QuadMesh.h"

class InstancedSystem
{
private:
	GLuint _instanceBufferID;
	glm::mat4* modelMatrices;
	QuadMesh _quadmesh;
	MeshManager _meshmanager;
	glm::mat4 _proj;  // projection matrix
	Shader _shader{ "Src/GraphicsSystem/Shader/instanced.vert", "Src/GraphicsSystem/Shader/instanced.frag" };
public:
	InstancedSystem(int windowWidth = 800, int windowHeight = 600);
	void Update();
};