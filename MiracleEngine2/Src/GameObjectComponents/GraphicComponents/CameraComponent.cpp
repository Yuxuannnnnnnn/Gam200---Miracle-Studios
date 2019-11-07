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
	if (document.HasMember("MovementSpeed") && document["MovementSpeed"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_movespeed = (document["MovementSpeed"].GetFloat());

	}

	if (document.HasMember("xZoom") && document["xZoom"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_xZoom = (document["xZoom"].GetFloat());
	}

	if (document.HasMember("yZoom") && document["yZoom"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_xZoom = (document["yZoom"].GetFloat());
	}
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}

void CameraComponent::Inspect()
{
	IComponentSystem::Inspect();
}


void CameraComponent::SetMoveSpeed(int num)
{
	_movespeed = num;
}
void CameraComponent::SetxZoom(int num)
{
	_xZoom = num;
}
void CameraComponent::SetyZoom(int num)
{
	_yZoom = num;
}