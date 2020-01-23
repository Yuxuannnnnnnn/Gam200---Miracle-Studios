#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Tools/MathLib/Math.h"

class CameraSystem
{
public:
	CameraSystem();
	float* GetCamMatrix();
	void Update();

	void SetPos_CamEditor(const size_t& in);
	void SetPos_CamEditor(Vector3& in);
	Vector3& GetPos_CamEditor();

	const float& GetZoom_CamEditor() const;
	void SetZoom_CamEditor(float& in);

private:
	size_t _mainCameraUId;

	Matrix4x4 _cameraMatrix;

	Vector3 _cameraEditorPos;
	float _cameraEditorzoom;
};