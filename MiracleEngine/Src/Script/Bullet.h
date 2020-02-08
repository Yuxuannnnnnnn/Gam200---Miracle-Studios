#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef BULLET_H
#define	BULLET_H

/*_bulletType
	0 unknown
	1 player
	2 turret // exploding player bullet
	3 enemy
*/

class Player; // forward declares
class Enemy;

class Bullet : public IScript2
{
private:
	bool _init, _justCollided;
	double _lifeTime;
	int _bulletType;
	double _bulletSpeed;
public:
	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Bullet();
	Bullet* Clone();

	int StringToInt(std::string& in);
	std::string IntToString(int bulletType);


	void Init()
	{
		_init = true;
		if (_bulletType == 1)
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(false);
	}

	void Update(double dt);

	void BulletCollisionPlayer(Collider2D* other);
	void BulletCollisionTurret(Collider2D* other);
	void BulletCollisionEnemy(Collider2D* other);

	void OnCollision2DTrigger(Collider2D* other);
};

#endif
