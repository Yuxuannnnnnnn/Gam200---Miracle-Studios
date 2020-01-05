#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef PICKUP_H
#define	PICKUP_H

enum class PickUp_Type
{
	NONE = 0,
	HEALTH_REGAN = 1,
	ROCKET_AMMO = 2,
};

class PickUps : public IScript
{
private:
	double _lifeTime;
	int _pickupType;
public:
	PickUps();

	void SerialiseComponent(Serialiser& document);

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) 
	{
	}

	void Inspect() 
	{

	}

	void Update(double dt);
};

#endif
