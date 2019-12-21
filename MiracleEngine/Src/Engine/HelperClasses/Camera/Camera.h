#pragma once

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "HelperClasses/Graphic/Elementbuffer.h"
#include "HelperClasses/Graphic/VertexBuffer.h"
#include <string>
#include "HelperClasses/Graphic/VertexArray.h"
#include "PrecompiledHeaders.h"
#include "Components/TransformComponent.h"
#include "Components/GraphicComponent.h"
#include "Components/CameraComponent.h"
#include "HelperClasses/Graphic/Shader.h"
#include "HelperClasses/Graphic/QuadMesh.h"
#include "HelperClasses/Graphic/TextureManager.h"

class Camera
{
public:
	glm::mat4 GetCamMatrix();
	void Update();
	void ZoomIn(float x);
	void ZoomOut(float x);
	void SetCameraPos(float x, float y);
	void MoveCameraX(float x);
	void MoveCameraY(float y);
private:
	glm::mat4 CamMatrix;
	float x_pos = 1.0f;
	float y_pos = 1.0f;
	float x_scale = 1.0f;
	float y_scale = 1.0f;
};