#include "PrecompiledHeaders.h"
#include "CameraComponent.h"


CameraComponent::CameraComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId)
{
	if (component)
	{
		CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(component);

	}
}

void CameraComponent::SerialiseComponent(Serialiser& document)
{
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}

void CameraComponent::Inspect()
{
}
