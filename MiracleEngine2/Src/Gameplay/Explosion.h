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

	void Update(double dt);

	void OnTrigger2DEnter(Collider2D* other);
};
#endif
