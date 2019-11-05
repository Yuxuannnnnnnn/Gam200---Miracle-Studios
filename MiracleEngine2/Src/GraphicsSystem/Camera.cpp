
#include "PrecompiledHeaders.h"
#include "Camera.h"

glm::mat4 Camera::GetCamMatrix()
{
	return glm::inverse(CamMatrix);
}

void Camera::Update(std::unordered_map < size_t, TransformComponent*>&  _transformList)
{
	for (auto& camComponentpair : EngineSystems::GetInstance()._gameObjectFactory->_CameraComponents)
	{

		size_t objID = camComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = _transformList[objID]; //Get transform from GameObjectID

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(x_pos
			, y_pos, 1));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
		glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(1.0f,1.0f, 1.0f));

		glm::mat4 mvp = model;
		CamMatrix = mvp;
		
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