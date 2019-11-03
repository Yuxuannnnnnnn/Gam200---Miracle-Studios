#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "LogicSystem/AiSystem.h"

#ifndef AICOMPONENT_H
#define	AICOMPONENT_H

enum class AiState { // state for FSM
	IDLE = 0,
	MOVING, // using pathfinding to player
	ATTACKING, // in range of player, direct movement
};

class Node; // forward declare from 'AiSys>PathFinding'

class AiComponent : public IComponentSystem
{
private:
	// Target(endPoint) Transform
	unsigned _state;
	Vector3 _destinationPos;
	GameObject* _target;
	std::vector<Node*> _path;
	Node* _nextNode;
	float _attackRange; // currently set to 1*_mapTileSize
public:
	//Constructor
	AiComponent(GameObject* target, GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	// CompName
	std::string ComponentName() const override;
	//void SerialiseComponent(Serialiser& document) override;
	//virtual void Inspect() override;


	// InUpEx
	void Init();
	void Update();
	void Exit();
	// GetDestination
	Vector3& GetDestinationPos();	// gets _target's position
// GetPosition(of Parent)
	Vector3& GetPosition();	// gets _parent's position
// GetPath
	std::vector<Node*>& GetPath();
// Move using path (toward _destination)
	void Move();
	void Move(Vector3 nextNodePos);
// FSM
	void FSM();
};

#endif
