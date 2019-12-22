#pragma once


// to do : move out of SystemGraphics


// a manager class to manage all the camera
#include <map>
#include <string>
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class CameraManager
{
public:
	void Init();
	void Update();               // update all the camera component
	glm::mat4 GetMainCamMatrix();

	bool IsEditorModeOn() const;
	void SetEditorMode(bool isEditorOn);

private:
	std::unordered_map<std::string, Camera> _cameraList;
	std::string _currCamera;  // current camera in use

	bool isEditorRunning = false;




	// to be removed later

	float x_pos = 1.0f;
	float y_pos = 1.0f;
	float x_scale = 1.0f;
	float y_scale = 1.0f;
};