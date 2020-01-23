#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Tools/MathLib/Math.h"

class CameraSystem
{
public:
	CameraSystem();
	const glm::mat4& GetCamMatrix();
	void Update();

	void SetPos_CamEditor(GameObject* in);
	void SetPos_CamEditor(Vector3& in);
	float GetZoom_CamEditor();
	void SetZoom_CamEditor(float in);

private:
	glm::mat4 _camMatrix;
	float _xPos;

	bool bUseEditorCamera;
	Vector3 cameraEditorPos;
	float zoom;
};