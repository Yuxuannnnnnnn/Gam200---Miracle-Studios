#include "PrecompiledHeaders.h"
#include "CameraSystem.h"

const glm::mat4& CameraSystem::GetCamMatrix()
{
	return _camMatrix;
}

void CameraSystem::Update()
{
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Z))
	{
		_xPos = _xPos + 1;
	}

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(_xPos
		, 0, 1));
	//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
	_camMatrix = translate;
}
