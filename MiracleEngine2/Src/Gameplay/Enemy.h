#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Enemy : public IScript
{
private:

	// Target(endPoint) Transform
	unsigned _state;
	Vector3 _destinationPos;
	GameObject* _target;
	std::vector<Node*> _path;
	Node* _nextNode;
	float _attackRange; // currently set to 1*_mapTileSize
	bool _init{ false };
	double _timer{ 0 };
	double _timeCooldown{ 1 };

public:

	int _health;

	void SerialiseComponent(Serialiser& document) 
	{
		if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
		{
			_health = (document["Health"].GetInt());
		}
	}


	//Constructor
	Enemy();


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

	void OnCollision2DTrigger(Collider2D* other);
};