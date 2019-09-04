#pragma once
#include <vector>

#include "../Isystem.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "../GameObject.h"
#include "../collision/collision.h"
#include "../main.h"
#include "vertex.h"
#include "../engine/engine.h"
#include <algorithm>

class GraphicSystem : public ISystem
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
private:
	glm::mat4 _proj;
	Vertex _vertex;
};