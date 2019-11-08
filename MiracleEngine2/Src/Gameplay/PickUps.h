#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

enum class PickUp_Type
{
	NONE = 0,
	HEALTH_REGAN = 1,
	ROCKET_AMMO = 2,
};

class PickUps : public IScript
{
private:

public:
	double _lifeTime;
	int _pickupType;

	PickUps() : _lifeTime{ -666.f }, _pickupType{ (int)PickUp_Type::NONE } {}

	void Update(double dt)
	{
		if (_lifeTime != -666.f)
		{
			_lifeTime -= dt;

			if (_lifeTime < 0)
				DestoryThis();
		}
	}

	void SerialiseComponent(Serialiser& document)
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
};