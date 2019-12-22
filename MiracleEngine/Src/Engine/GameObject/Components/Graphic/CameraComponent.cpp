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

void CameraComponent::SerialiseComponent(Serialiser& document)
{

}

void CameraComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{

}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}

void CameraComponent::Inspect()
{
	IComponent::Inspect();
}


