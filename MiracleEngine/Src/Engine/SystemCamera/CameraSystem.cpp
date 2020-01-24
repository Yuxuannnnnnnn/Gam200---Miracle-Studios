#include "PrecompiledHeaders.h"
#include "CameraSystem.h"

#define CAMERA_MOVESPEED 1.f
#define CAMERA_SCALESPEED 0.5f

CameraSystem::CameraSystem() : _mainCameraUId{ 0 }, _cameraEditorPos{ 0.f, 0.f, 1.f }, _cameraEditorzoom{ 1.f }
{}

void CameraSystem::Update()
{
#ifdef LEVELEDITOR
	if (MyImguiSystem._editorMode)
	{
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
			_cameraEditorPos._x += CAMERA_MOVESPEED;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
			_cameraEditorPos._x -= CAMERA_MOVESPEED;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_UP))
			_cameraEditorPos._y -= CAMERA_MOVESPEED;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
			_cameraEditorPos._y += CAMERA_MOVESPEED;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_PAGEUP))
		{
			_cameraEditorzoom += CAMERA_SCALESPEED;
			if (_cameraEditorzoom > 15.f)
				_cameraEditorzoom = 15.f;

			//_cameraEditorPos /= _cameraEditorzoom;
		}
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_PAGEDOWN))
		{
			_cameraEditorzoom -= CAMERA_SCALESPEED;
			if (_cameraEditorzoom < 0.1f)
				_cameraEditorzoom = 0.1f;

			//_cameraEditorPos /= _cameraEditorzoom;

		}
	}
#else
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Z))
	{
		_xPos = _xPos + 1;
	}
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(_xPos, 0, 1));
	//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
	_camMatrix = translate;
#endif
}

float* CameraSystem::GetCamMatrix()
{

#ifdef LEVELEDITOR
	// calculate model matrix = TRS
	Mtx44 translate = Mtx44::CreateTranslation(_cameraEditorPos);
	_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ _cameraEditorzoom ,_cameraEditorzoom ,1.f});
#else

#endif
	/*
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(cameraEditorPos._x, cameraEditorPos._y, 1.f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 1.f));
		_camMatrix = translate * scale;
	*/

	return _cameraMatrix.m;
}

void CameraSystem::SetPos_CamEditor(const size_t& in)
{
	if (in)
	{
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[in];

		if (transform)
		{
			_cameraEditorPos = Vec3{ -transform->GetPos()._x, -transform->GetPos()._y, -transform->GetPos()._z };
			_cameraEditorzoom = 1.f;
		}
	}
}
void CameraSystem::SetPos_CamEditor(Vector3& in)
{
	_cameraEditorPos = in;
}

Vector3& CameraSystem::GetPos_CamEditor() 
{
	return _cameraEditorPos;
}

const float& CameraSystem::GetZoom_CamEditor() const
{
	return _cameraEditorzoom;
}
void CameraSystem::SetZoom_CamEditor(float& in) 
{
	_cameraEditorzoom = in;
}
