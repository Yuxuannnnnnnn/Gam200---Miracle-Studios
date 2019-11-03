#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Turret : public IScript
{
private:
	bool _init;
	unsigned _state;
	GameObject* _target;
	float _attackRange; // currently set to 1*_mapTileSize
public:
	//Constructor
	Turret();

	int _health;

	// InUpEx
	void Init();
	void Update(double dt);
	void Exit();

// GetDestination
	Vector3& GetDestinationPos();	// gets _target's position
// GetPosition(of Parent)
	Vector3& GetPosition();	// gets _parent's position

// Search Target
	void SearchTarget();
	void ShootTarget();
	void RotateToTarget();

	// FSM
	void FSM();
};