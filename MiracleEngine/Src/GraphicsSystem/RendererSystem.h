#pragma once
#include "PrecompiledHeaders.h"

// renderer System expose 3 function to user: DrawPoint, DrawLine, DrawWireFrameQuad 

//#include "GameObjectComponents/GameObject.h"
//
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//
//#include "Elementbuffer.h"
//#include "VertexBuffer.h"
//#include "MeshManager.h"
#include "Shader.h"
#include "GameObjectComponents/TransformComponent.h"
#include "GameObjectComponents/GraphicComponent.h"

class RendererSystem
{
private:
	MeshManager _meshmanager;
	glm::mat4 _proj;  // projection matrix
	Shader _shader{ "Src/GraphicsSystem/Shader/basic.vert", "Src/GraphicsSystem/Shader/basic.frag" };
public:
	RendererSystem(int windowWidth = 800, int windowHeight = 600);
	void Update();
	void DrawPoint(int x, int y, int size);
	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize);
	void DrawLine(int x1, int y1, int x2, int y2);
	void Draw(const TransformComponent& transform, const GraphicComponent& graphic);
};