#pragma once

#include "UIMesh.h"
#include "../Engine/GameObject/Components/Graphic/UIComponent.h"
#include <map>
#include "../SystemGraphics/Shader.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class UIRenderer
{
public:
	UIRenderer();
	void Update(std::unordered_map<size_t, IComponent*> uiMap, const glm::mat4& proj);
private:
	UIMesh _uiMesh;
	Shader* _uiShader;
};