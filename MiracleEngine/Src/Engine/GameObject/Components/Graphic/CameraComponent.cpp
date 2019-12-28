#include "PrecompiledHeaders.h"
#include "CameraComponent.h"


CameraComponent::CameraComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId)
{
	if (component)
	{
		CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(component);

	}
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}




