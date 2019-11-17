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
	void SerialiseComponent(Serialiser& document);

	void Update(double dt);

	void OnCollision2DTrigger(Collider2D* other);
};
#endif
