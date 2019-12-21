#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"


PickUps::PickUps() : _lifeTime{ -666.f }, _pickupType{ (int)PickUp_Type::NONE }
{}



void PickUps::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_lifeTime = (document["Lifetime"].GetFloat());
	}
	if (document.HasMember("PickUps_Type") && document["PickUps_Type"].IsInt())	//Checks if the variable exists in .Json file
	{
		_pickupType = (document["PickUps_Type"].GetInt());
	}
}

void PickUps::Update(double dt)
{
	if (_lifeTime != -666.f)
	{
		_lifeTime -= dt;

		if (_lifeTime < 0)
			DestoryThis();
	}
}
