#pragma once
// renderer System expose 3 function to user: DrawPoint, DrawLine, DrawWireFrameQuad 

#include "../Engine/GameObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "Shader.h"
#include "QuadMesh.h"
#include "TextureManager.h"
#include "Animation.h"
#include "PlayerMesh.h"

class RendererSystem
{
private:
	TextureManager _textureManager;
	QuadMesh _quadmesh;
	PlayerMesh _playermesh;
	MeshManager _meshmanager;
	Animation _animation;
	glm::mat4 _proj;  // projection matrix
	Shader _shader{ "Src/GraphicsSystem/Shader/basic.vert", "Src/GraphicsSystem/Shader/basic.frag" };
public:
	RendererSystem(int windowWidth = 800, int windowHeight = 600);
	void Update(double dt, int num);
	void DrawPoint(int x, int y, int size);
	void DrawWireFrameQuad(int xpos, int ypos, int xsize, int ysize);
	void DrawLine(int x1, int y1, int x2, int y2);
	
};