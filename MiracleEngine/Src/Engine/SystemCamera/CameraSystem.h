#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Tools/MathLib/Math.h"

class CameraSystem
{
public:
	CameraSystem();

	void Init();
	void Update();


	void SetPos_CamEditor(const size_t& in);
	void SetPos_CamEditor(Vector3& in);

	Vector3& GetGlobalPos_CamEditor();
	Vector3& GetPos_CamEditor();

	const float& GetZoom_CamEditor() const;
	void SetZoom_CamEditor(float& in);

	///////////////////////////////////////////////////////////////////////////////////

	// use by both gameplay and editor 

	float* GetCamMatrix();
	Vector3 GetCameraPos();
	float GetCameraZoom();

	// interact gameplay and script

	void SetMainCamera(size_t mainCameraUId);
	size_t GetMainCameraUId();
	const Vector3& GetMainCameraPos() const;

	
	void FindMainCamera();
private:
	size_t _mainCameraUId;

	Matrix4x4 _cameraMatrix;

	///////////////////////////////////////////////////////////////////////////////////
	Vector3 _globalCameraEditorPos;
	Vector3 _cameraEditorPos;
	float _cameraEditorzoom;
};