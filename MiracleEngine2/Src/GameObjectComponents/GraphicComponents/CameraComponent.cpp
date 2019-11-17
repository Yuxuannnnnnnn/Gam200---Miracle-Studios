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
		_yZoom = (document["yZoom"].GetFloat());
	}
}

void CameraComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetFloat(_movespeed);
	prototypeDoc.AddMember("MovementSpeed", value);
	value.Clear();

	value.SetFloat(_xZoom);
	prototypeDoc.AddMember("xZoom", value);
	value.Clear();

	value.SetFloat(_yZoom);
	prototypeDoc.AddMember("yZoom", value);
	value.Clear();
}



std::string CameraComponent::ComponentName() const
{
	return std::string("Camera Component");
}

void CameraComponent::Inspect()
{
	IComponentSystem::Inspect();
}


void CameraComponent::SetMoveSpeed(float num)
{
	_movespeed = num;
}
void CameraComponent::SetxZoom(float num)
{
	_xZoom = num;
}
void CameraComponent::SetyZoom(float num)
{
	_yZoom = num;
}