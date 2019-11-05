#pragma once

#ifndef GRAPHICSYSTEM_H
#define GRAPHICSYSTEM_H

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include <string>
#include "VertexArray.h"
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"
#include "GameObjectComponents/GraphicComponents/GraphicComponent.h"
#include "Shader.h"
#include "QuadMesh.h"
#include "TextureManager.h"

#include "Camera.h"
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

	std::unordered_map < size_t, GraphicComponent* > _spriteList;
	std::unordered_map < size_t, TransformComponent*>  _transformList;

	void Update(double dt);
	void Exit();
	//RenderMode _renderMode = None;
	int num = 0;


	GraphicsSystem(int windowWidth, int windowHeight) : _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
		-(float)windowHeight / 2, (float)windowHeight / 2, -15.0f, 15.0f) }
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		
	}

	Camera& GetCamera()
	{
		return _camera;
	}


private:
	void ClearScreen() const;
	TextureManager _textureManager;
	Shader _shader{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" };
	glm::mat4 _proj;
	QuadMesh _quadmesh;
	Camera _camera;
	//RendererSystem _renderer;
	//InstancedSystem _instancedRenderer;

};

#endif

