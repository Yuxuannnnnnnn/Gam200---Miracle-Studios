#pragma once

// a manager class to manage all the camera
#include <map>
#include <string>
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class CameraManager
{
public:
	// update the camera component

	void Update();
	glm::mat4 GetMainCamMatrix();

private:
	std::unordered_map<std::string, Camera> _cameraList;
	std::string _currCamera;  // current camera in use

	// to be removed later

	float x_pos = 1.0f;
	float y_pos = 1.0f;
	float x_scale = 1.0f;
	float y_scale = 1.0f;
};