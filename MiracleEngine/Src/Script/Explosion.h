#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef EXPLOSION_H
#define	EXPLOSION_H

class Enemy; // forward declare

class Explosion : public IScript2
{
private:
	double _lifeTime;
	int _radius;
public:
	Explosion();
	Explosion* Clone();
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	void Update(double dt);

	void OnTrigger2DEnter(Collider2D* other);
	void OnCollision2DStay(Collider2D* other);	
};
#endif
