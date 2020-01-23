#include "PrecompiledHeaders.h"
#include "CameraSystem.h"

CameraSystem::CameraSystem() : bUseEditorCamera{ false }, zoom{ 1.f }
{}

const glm::mat4& CameraSystem::GetCamMatrix()
{
	return _camMatrix;
}

void CameraSystem::Update()
{
	bUseEditorCamera = (MyImguiSystem._editorMode) ? true : false;
	if (bUseEditorCamera)
	{
		float moveSpeed = 1.f;
		float scaleSpeed = 0.1f;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
			cameraEditorPos._x += moveSpeed;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
			cameraEditorPos._x -= moveSpeed;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_UP))
			cameraEditorPos._y -= moveSpeed;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
			cameraEditorPos._y += moveSpeed;
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_PAGEUP))
		{
			zoom += scaleSpeed;
			if (zoom > 15.f)
				zoom = 15.f;
		}
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_PAGEDOWN))
		{
			zoom -= scaleSpeed;
			if (zoom < 0.1f)
				zoom = 0.1f;
		}
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(cameraEditorPos._x, cameraEditorPos._y, 1.f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 1.f));
		_camMatrix = translate * scale;
	}
	else
	{
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Z))
		{
			_xPos = _xPos + 1;
		}
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(_xPos, 0, 1));
		//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		_camMatrix = translate;
	}
}

void CameraSystem::SetPos_CamEditor(GameObject* in)
{
	if (in && in->GetComponent(ComponentId::CT_Transform))
		cameraEditorPos = ((TransformComponent*)in->GetComponent(ComponentId::CT_Transform))->GetPos();
}
void CameraSystem::SetPos_CamEditor(Vector3& in)
{
	cameraEditorPos = in;
}
float CameraSystem::GetZoom_CamEditor()
{
	return zoom;
}
void CameraSystem::SetZoom_CamEditor(float in)
{
	zoom = in;
}
