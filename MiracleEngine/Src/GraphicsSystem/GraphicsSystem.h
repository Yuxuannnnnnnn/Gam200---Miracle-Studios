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
#include "InstancedSystem.h"
#include "../GameObjectComponents/TransformComponent.h"
#include "../GameObjectComponents/GraphicComponent.h"
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
	void Init();
	void Update(const TransformComponent* transform, const GraphicComponent* graphic);
	void Exit();
	RenderMode _renderMode = None;
	int num = 0;
private:
	void ClearScreen() const;
	MeshManager _meshmanager;
	RendererSystem _renderer;
	InstancedSystem _instancedRenderer;
	
};