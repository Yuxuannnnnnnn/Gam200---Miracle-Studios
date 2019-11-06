#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Explosion : public IScript
{
private:

public:
	float _lifeTime;

	Explosion() : _lifeTime{ -666.f } {}

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