#include "PrecompiledHeaders.h"
#include "CameraSystem.h"

#define CAMERA_MOVESPEED 1.f
#define CAMERA_SCALESPEED 0.2f

CameraSystem::CameraSystem() : _mainCameraUId{ 0 }, _globalCameraEditorPos{ 0.f, 0.f, 1.f }, _cameraEditorPos{ 0.f, 0.f, 1.f }, _cameraEditorzoom{ 1.f }
{
}

void CameraSystem::Init()
{
	FindMainCamera();
}

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

			//std::cout << _cameraEditorzoom << std::endl;

			//_cameraEditorPos /= _cameraEditorzoom;
		}
		if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_PAGEDOWN))
		{
			_cameraEditorzoom -= CAMERA_SCALESPEED;
			if (_cameraEditorzoom < 0.1f)
				_cameraEditorzoom = 0.1f;

			//std::cout << _cameraEditorzoom << std::endl;

			//_cameraEditorPos /= _cameraEditorzoom;

		}
	}

	_cameraEditorPos = _globalCameraEditorPos * _cameraEditorzoom;
#endif
}

void CameraSystem::SetPos_CamEditor(const size_t& in)
{
	if (in)
	{
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[in];

		if (transform)
		{
			_globalCameraEditorPos = Vec3{ -transform->GetPos()._x, -transform->GetPos()._y, 1.f };
			_cameraEditorzoom = 1.f;
		}
	}
	else
	{
		_globalCameraEditorPos = Vec3{ 0.f, 0.f, 1.f };
		_cameraEditorzoom = 1.f;
	}
}
void CameraSystem::SetPos_CamEditor(Vector3& in)
{
	_globalCameraEditorPos = in;
}

Vector3& CameraSystem::GetGlobalPos_CamEditor()
{
	return _globalCameraEditorPos;
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

///////////////////////////////////////////////////////////////////////////////////

float* CameraSystem::GetCamMatrix()
{

#ifdef LEVELEDITOR

	if (MyImguiSystem._editorMode)
	{
		// calculate model matrix = TRS
		Mtx44 translate = Mtx44::CreateTranslation(_cameraEditorPos);
		_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ _cameraEditorzoom ,_cameraEditorzoom ,1.f });
	}
	else
	{
		CameraComponent* camera = (CameraComponent*)GetComponentMap(Camera)[_mainCameraUId];
		TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[_mainCameraUId];

		if (!camera || !transform)
		{
			Mtx44 translate = Mtx44::CreateTranslation(Vec3{ 0.f,0.f,1.f });
			_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ 1.f ,1.f ,1.f });
		}
		else
		{
			Mtx44 translate = Mtx44::CreateTranslation(Vec3{ -transform->GetPos()._x * camera->_cameraZoom,-transform->GetPos()._y * camera->_cameraZoom,1.f });
			_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ camera->_cameraZoom ,camera->_cameraZoom ,1.f });
		}
	}
#else
	CameraComponent* camera = (CameraComponent*)GetComponentMap(Camera)[_mainCameraUId];
	TransformComponent* transform = (TransformComponent*)GetComponentMap(Transform)[_mainCameraUId];

	if (!camera || !transform)
	{
		Mtx44 translate = Mtx44::CreateTranslation(Vec3{ 0.f,0.f,1.f });
		_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ 1.f ,1.f ,1.f });
	}
	else
	{
		Mtx44 translate = Mtx44::CreateTranslation(Vec3{ -transform->GetPos()._x,-transform->GetPos()._y,1.f });
		_cameraMatrix = translate * Mtx44::CreateRotationZ(0) * Mtx44::CreateScale(Vec3{ camera->_cameraZoom ,camera->_cameraZoom ,1.f });
	}
#endif
	/*
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(cameraEditorPos._x, cameraEditorPos._y, 1.f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 1.f));
		_camMatrix = translate * scale;
	*/

	return _cameraMatrix.m;
}

Vector3 CameraSystem::GetCameraPos()
{
#ifdef LEVELEDITOR

	if (MyImguiSystem._editorMode)
	{
		return _globalCameraEditorPos;
	}
	else
	{
		TransformComponent* obj = (TransformComponent*)GetComponentMap(Transform)[_mainCameraUId];

		if (!obj)
			return Vec3{0.f,0.f,1.f};

		return Vec3{-obj->GetPos()._x, -obj->GetPos()._y, 1.f};
	}
#else
	TransformComponent* obj = (TransformComponent*)GetComponentMap(Transform)[_mainCameraUId];

	if (!obj)
		return Vec3{ 0.f,0.f,1.f };

	return Vec3{ -obj->GetPos()._x, -obj->GetPos()._y, 1.f };
#endif
}

float CameraSystem::GetCameraZoom()
{
#ifdef LEVELEDITOR
	if (MyImguiSystem._editorMode)
	{
		return _cameraEditorzoom;
	}
	else
	{
		CameraComponent* obj = (CameraComponent*)GetComponentMap(Camera)[_mainCameraUId];

		if (!obj)
			return 1.f;

		return obj->_cameraZoom;
	}
#else
	CameraComponent* obj = (CameraComponent*)GetComponentMap(Camera)[_mainCameraUId];

	if (!obj)
		return 1.f;

	return obj->_cameraZoom;
#endif
}

void CameraSystem::SetMainCamera(size_t mainCameraUId)
{
	for (auto& it : GetComponentMap(Camera))
	{
		if (it.first == mainCameraUId)
		{
			_mainCameraUId = mainCameraUId;
			continue;
		}

		CameraComponent* obj = (CameraComponent*)it.second;
		if(obj)
			obj->SetMainCamera(false);
	}
}

size_t CameraSystem::GetMainCameraUId()
{
	return _mainCameraUId;
}

const Vector3& CameraSystem::GetMainCameraPos() const
{
	TransformComponent* obj = (TransformComponent*)GetComponentMap(Transform)[_mainCameraUId];

	if (!obj)
		return Vec3{};

	return obj->GetPos();
}

void CameraSystem::FindMainCamera()
{
	if (_mainCameraUId)
	{
		CameraComponent* obj = (CameraComponent*)GetComponentMap(Camera)[_mainCameraUId];

		if (obj && obj->GetEnable())
			return;
	}

	for (auto& it : GetComponentMap(Camera))
	{
		if (!it.second)
			return;

		if (((CameraComponent*)it.second)->isMainCamera())
		{
			_mainCameraUId = it.first;
			return;
		}
	}
}