#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "LogicSystem/AiSystem.h"

#ifndef AICOMPONENT_H
#define	AICOMPONENT_H

enum class AiState { // state for FSM
	IDLE = 0,
	MOVING,
	ATTACKING,
};

class Node; // forward declare from 'AiSys>PathFinding'

class AiComponent : public IComponentSystem
{
private:
	// Target(endPoint) Transform
	Vector3 _destination;
	std::vector<Node*> _path;
public:
	//Constructor
	AiComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	AiComponent(size_t id = 0);
// CompName
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	virtual void Inspect() override;
	
// InUpEx
	void Init();
	void Update(std::vector<Node>& tilemap);
	void Exit();
// GetDestination
	Vector3& GetDestination();	// gets _target's position
// GetPosition(of Parent)
	Vector3& GetPosition();	// gets _parent's position
// GetPath
	std::vector<Node*>& GetPath();
// Move using path (toward _destination)
	void Move();
};

#endif
