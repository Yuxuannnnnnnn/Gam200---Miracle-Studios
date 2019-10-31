#pragma once
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include <string>
#include "GraphicsSystem/RendererSystem.h"
#include "VertexArray.h"
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"
#include "GameObjectComponents/GraphicComponents/GraphicComponent.h"
#include "Shader.h"
#include "QuadMesh.h"
#include "TextureManager.h"
enum RenderMode
{
	None,
	Instance,
	Font,
	Font2
};
class GraphicsSystem
{
public:

	void Update(const std::unordered_map < size_t, GraphicComponent* >& graphicmap,
		std::unordered_map < size_t, TransformComponent* >& transformmap);
	void Exit();
	//RenderMode _renderMode = None;
	int num = 0;


	GraphicsSystem(int windowWidth, int windowHeight) : _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2) }
	{

	}



private:
	void Test();
	void ClearScreen() const;
	TextureManager _textureManager;
	MeshManager _meshmanager;
	Shader _shader{ "Src/GraphicsSystem/Shader/basic.vert", "Src/GraphicsSystem/Shader/basic.frag" };
	glm::mat4 _proj;
	QuadMesh _quadmesh;
	//RendererSystem _renderer;
	//InstancedSystem _instancedRenderer;

};