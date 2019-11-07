#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Bullet_T : public IScript
{
private:

public:
	float _lifeTime;

	Bullet_T() : _lifeTime{ -666.f } {}

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