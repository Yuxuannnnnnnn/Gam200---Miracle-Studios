#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef ENEMYAI_H
#define	ENEMYAI_H

class EnemyAI : public IScript
{
private:
	bool _init;
	// Target(endPoint) Transform
	unsigned _state;
	Vector3 _destinationPos;
	GameObject* _target;
	std::vector<Node*> _path;
	Node* _nextNode;
	float _attackRange; // currently set to 1*_mapTileSize
public:
	//Constructor
	EnemyAI();


	// InUpEx
	void Init();
	void Update(double dt);
	void Exit();
	// GetDestination
	Vector3& GetDestinationPos();	// gets _target's position
// GetPosition(of Parent)
	Vector3& GetPosition();	// gets _parent's position
// GetPath
	std::vector<Node*>& GetPath();
	// Move using path (toward _destination)
	void Move();
	void MoveNode();
	// FSM
	void FSM();
};

#endif
