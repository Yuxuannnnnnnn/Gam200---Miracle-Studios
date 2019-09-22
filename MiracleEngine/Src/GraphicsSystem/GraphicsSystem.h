#pragma once
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "GameObjectComponents/GameObject.h"
#include <string>
#include "GraphicsSystem/RendererSystem.h"
#include "VertexArray.h"

#include "GameObjectComponents/TransformComponent.h"
#include "GameObjectComponents/GraphicComponent.h"



class GraphicsSystem
{
public:
	void Init();
	void Update();
	void Exit();

private:
	//Takes in the transform and graphic Component of every GameObject
	void Draw(IComponentSystem * transformComponent, IComponentSystem * graphicComponent);

	void ClearScreen() const;
	glm::mat4 _proj;
	GLuint _shader;
	MeshManager _meshmanager;
	RendererSystem _renderer;
};