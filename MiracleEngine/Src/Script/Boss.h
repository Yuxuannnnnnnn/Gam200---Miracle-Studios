#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef BOSS_H
#define	BOSS_H

//enum class BossStates {
//	DEAD = 0,
//
//};
//
//class Boss : public IScript2
//{
//private:
//// Logic Data - General
//	bool _init;
//	int _health, _healthMax, _healthRage;
//	double _timerAttackNormal, _frequencyAttackNormal;
//	double _timerAttackRage, _frequencyAttackRage;
//// Logic - Behaviour
//	GameObject* _target;
//	int _state;
//
//public:
//	void SerialiseComponent(Serialiser& document)
//	{
//
//	}
//	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
//	{
//
//	}
//	void Inspect()
//	{
//
//	}
//	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
//	{
//	}
//
//	Boss();
//	Boss* Clone();
//	void Init();
//	void Update(double dt);
//
//	Vector3& GetDestinationPos();	// gets _target's position
//	Vector3& GetPosition();	// gets _parent's position
//
//	void FSM();	
//
//	void OnCollision2DTrigger(Collider2D* other);
//};

#endif
