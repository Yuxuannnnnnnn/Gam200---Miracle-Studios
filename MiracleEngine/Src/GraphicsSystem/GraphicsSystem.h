#pragma once
#include "PrecompiledHeaders.h"
#include <glew.h>
#include "MeshManager.h"
#include "GameObjectComponents/GraphicComponent.h"
#include "GameObjectComponents/TransformComponent.h"

class GraphicsSystem
{
public:
	void Init();
	void Update(const std::map < size_t, TransformComponent* >& transformComponent,
		const std::map < size_t, GraphicComponent* >& graphicComponent);
	void Exit();

private:
	//Takes in the transform and graphic Component of every GameObject
	//void Draw();

	void ClearScreen() const;

	glm::mat4 _proj;
	GLuint _shader;
	MeshManager _meshmanager;
	//RendererSystem _renderer;
};