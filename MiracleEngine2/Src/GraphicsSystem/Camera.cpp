
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
		if (camComponentpair.second->GetParentId() < 1000)
			continue;

		size_t objID = camComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

		TransformComponent x = *transformComponent;

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(transformComponent->GetPos()._x 
			, transformComponent->GetPos()._y, 1));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		 CamMatrix = translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(transformComponent->GetScale()._x, transformComponent->GetScale()._y, 1.0f));
	}
	
}

void Camera::moveX(int x)
{
	x_pos += x;
}

void Camera::moveY(int y)
{
	y_pos += y;
}