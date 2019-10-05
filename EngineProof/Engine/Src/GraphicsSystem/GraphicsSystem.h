#pragma once
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include "MeshManager.h"
#include "..\GameObjects\GameObject.h"
#include <string>
#include "GraphicsSystem/RendererSystem.h"
#include "VertexArray.h"

#include "InstancedSystem.h"
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
	void Update(double dt);
	void Exit();
	RenderMode _renderMode = None;
	int num = 0;
private:
	void ClearScreen() const;
	MeshManager _meshmanager;
	RendererSystem _renderer;
	InstancedSystem _instancedRenderer;
	
};