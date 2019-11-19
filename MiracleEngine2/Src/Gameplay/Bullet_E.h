#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef BULLET_E_H
#define	BULLET_E_H

class Bullet_E : public IScript
{
private:
	double _lifeTime;
public:
	Bullet_E();

	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Lifetime") && document["Lifetime"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_lifeTime = (document["Lifetime"].GetFloat());
		}
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetDouble(_lifeTime);
		prototypeDoc.AddMember("Lifetime", value);
		value.Clear();
	}

	void Inspect() override
	{
		ImGui::Spacing();
		ImGui::InputDouble("Lifetime ", &_lifeTime);
		ImGui::Spacing();
	}

	void Update(double dt);

	void OnCollision2DTrigger(Collider2D* other);
};
#endif
