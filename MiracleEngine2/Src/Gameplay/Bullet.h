#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Bullet : public IScript
{
private:

public:
	double _lifeTime;

	Bullet() : _lifeTime{ -666.f } {}

	void Update(double dt);

	void OnTrigger2DEnter(Collider2D* other);


	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_lifeTime = (document["Lifetime"].GetFloat());
		}
	}
};