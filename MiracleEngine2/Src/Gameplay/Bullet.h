#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Bullet : public IScript
{
private:

public:
	float _lifeTime;

	Bullet() : _lifeTime{ -666.f } {}

	void Update(double dt);

	void SerialiseComponent(Serialiser& document);

	void OnCollision2DTrigger(Collider2D* other);
};