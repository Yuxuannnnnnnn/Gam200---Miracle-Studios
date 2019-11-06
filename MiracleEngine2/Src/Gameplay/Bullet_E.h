#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Bullet_E : public IScript
{
private:

public:
	double _lifeTime;

	Bullet_E() : _lifeTime{ -666.f } {}

	void Update(double dt);

	void OnCollision2DTrigger(Collider2D* other);


	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_lifeTime = (document["Lifetime"].GetFloat());
		}
	}
};