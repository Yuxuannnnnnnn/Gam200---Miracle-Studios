#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef BULLET_T_H
#define	BULLET_T_H

class Bullet_T : public IScript
{
private:
	double _lifeTime;
public:
	Bullet_T();

	void SerialiseComponent(Serialiser& document) override
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