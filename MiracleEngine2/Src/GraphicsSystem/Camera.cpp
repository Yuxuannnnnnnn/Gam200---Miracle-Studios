
#include "PrecompiledHeaders.h"
#include "Camera.h"

glm::mat4 Camera::GetCamMatrix()
{
	return glm::inverse(CamMatrix);
}

void Camera::Update(std::unordered_map < size_t, TransformComponent*>&  _transformList)
{
	for (auto& camComponentpair : EngineSystems::GetInstance()._gameObjectFactory->getCameraComponent())
	{
		if (camComponentpair.second->GetParentId() < 1000 || camComponentpair.second->GetParentPtr()->GetDestory())
			continue;

		size_t objID = camComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

		if (!transformComponent)
			continue;

		TransformComponent x = *transformComponent;

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(x_pos 
			, y_pos, 1));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		 CamMatrix = translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(x_scale, y_scale, 1.0f));
	}
	
}

void Camera::MoveCameraX(float x)
{
	x_pos += x;
}

void Camera::MoveCameraY(float y)
{
	y_pos += y;
}
void Camera::ZoomOut(float x)
{
	x_scale += x;
	y_scale += x;
}

void Camera::ZoomIn(float x)
{
	x_scale -= x;
	y_scale -= x;
}

void Camera::SetCameraPos(float x, float y)
{
	x_pos = x;
	y_pos = y;
}