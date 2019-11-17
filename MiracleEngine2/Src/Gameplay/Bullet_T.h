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
	void SerialiseComponent(Serialiser& document);

	void Update(double dt);

	void OnCollision2DTrigger(Collider2D* other);
};
#endif