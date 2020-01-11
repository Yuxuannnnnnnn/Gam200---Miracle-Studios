#include "PrecompiledHeaders.h"
#include "CameraManager.h"

// to do : move out of SystemGraphics

void CameraManager::Init()
{
}

void CameraManager::Update()
{
	// update all the camera component
	// check which is main camera
	// update view matrix

}

glm::mat4 CameraManager::GetMainCamMatrix()
{
	for (auto& camComponentpair : MyComponentManger._CameraComponents)
	{
		if (camComponentpair.second->GetParentId() < 1000 || camComponentpair.second->GetParentPtr()->GetDestory())
			continue;

		size_t objID = camComponentpair.first;	//Get GameObjectID
		TransformComponent* transformComponent = MyComponentManger._transformComponents[objID]; //Get transform from GameObjectID

		if (!transformComponent)
			continue;

		TransformComponent x = *transformComponent;

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(x_pos
			, y_pos, 1));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), transformComponent->GetRotate(), glm::vec3(0, 0, 1));
		return translate * rotate * glm::scale(glm::mat4(1.0f),
			glm::vec3(x_scale, y_scale, 1.0f));
	}
}

bool CameraManager::IsEditorModeOn() const
{
	return isEditorRunning;
}

void CameraManager::SetEditorMode(bool isEditorOn)
{
	isEditorRunning = isEditorOn;
}
