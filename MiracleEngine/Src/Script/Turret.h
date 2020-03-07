#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef TURRET_H
#define	TURRET_H

class Turret : public IScript2
{
private:
// Logic Data - General
	int _health, _healthMax;
// Logic - Behaviour
	GameObject* _target;
	size_t _targetUid;
	int _state;
	double _timerAttack, _timeAttackCooldown;	
	int _attackRangeShoot; // currently set to 1*_mapTileSize
// Logic Data - Animation
	double _deployTime, _aliveTime;
	bool _shooting;
	int _animState, _animStatePrev; // 1==StartIdle, 2==StartShoot

	GameObject* _turretBase;
	Vec3 _deployScale;

	TransformComponent* _transform;

public:
	void SerialiseComponent(Serialiser& document);
	//Function Not Needed for scripts
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();

	Turret();
	Turret* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	Vector3& GetDestinationPos();	// gets _target's position
	Vector3& GetPosition();	// gets _parent's position

// Attack Logic
	void SearchTarget();
	void ShootTarget();
	void RotateToTarget();

	void FSM();
};

#endif
