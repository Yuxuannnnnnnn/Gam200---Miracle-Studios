#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

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

class Bullet : public IScript
{
private:
	double _lifeTime;
	int _bulletType;
	double _bulletSpeed;
public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	Bullet();

	int StringToInt(std::string& in);
	std::string IntToString(int bulletType);

	void Update(double dt);

	void BulletCollisionPlayer(ICollider2D* other);
	void BulletCollisionTurret(ICollider2D* other);
	void BulletCollisionEnemy(ICollider2D* other);

	void OnCollision2DTrigger(ICollider2D* other);
};

#endif
