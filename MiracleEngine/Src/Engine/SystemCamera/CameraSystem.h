#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class CameraSystem
{
public:
	const glm::mat4& GetCamMatrix();
	void Update();

private:
	glm::mat4 _camMatrix;
	float _xPos;
};