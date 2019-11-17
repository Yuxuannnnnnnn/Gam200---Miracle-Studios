#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef BULLET_H
#define	BULLET_H

class Bullet : public IScript
{
private:
	double _lifeTime;
public:
	Bullet();
	void SerialiseComponent(Serialiser& document);

	void Update(double dt);

	void OnCollision2DTrigger(Collider2D* other);
};

#endif
