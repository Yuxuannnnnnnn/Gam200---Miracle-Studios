#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef EXPLOSION_H
#define	EXPLOSION_H

class Explosion : public IScript
{
private:
	double _lifeTime;
public:
	Explosion();
	void SerialiseComponent(Serialiser& document);

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{

	}

	void Inspect() override
	{

	}

	void Update(double dt);

	void OnTrigger2DEnter(ICollider2D* other);
};
#endif
