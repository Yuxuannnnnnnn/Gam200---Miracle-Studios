#pragma once
#include <vector>
#include "RenderObject.h"

class Renderer
{
public:
	void Update(const std::vector<std::vector<RenderObject>>&_renderObjects, const glm::mat4& proj) const;
};