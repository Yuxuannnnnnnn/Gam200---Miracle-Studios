#pragma once

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
#include "GameObjectComponents/GraphicComponents/CameraComponent.h"
#include "Shader.h"
#include "QuadMesh.h"
#include "TextureManager.h"

class Camera
{
public:
	glm::mat4 GetCamMatrix();
	void Update(std::unordered_map < size_t, TransformComponent*>&  _transformList);
	void moveX(int x);
	void moveY(int y);
private:
public:
	glm::mat4 CamMatrix;
	float x_pos;
	float y_pos;
};