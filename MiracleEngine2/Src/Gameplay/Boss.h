#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Boss : public IScript												// NOTE NOTE NOTE NOTE -- THIS ISNT DONE AT ALL, WILL SETTLE THIS AFTER I DO THE LOGIC CHANGES :BRANDON
{
private:

	// Target(endPoint) Transform
	unsigned _state;
	Vector3 _destinationPos;
	GameObject* _target;
	std::vector<Node*> _path;
	Node* _nextNode;
	Node* _destNode;
	float _attackRange; // currently set to 1*_mapTileSize
	bool _init{ false };
	double _timer{ -1.0 };
	double _timeCooldown{ 5 };
	double _timerAttack{ 0 };
	double _timerAttackCooldown{ 1 };

public:
	int _enemyType;
	int _health;

	void SerialiseComponent(Serialiser& document) 
	{
		if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
		{
			_health = (document["Health"].GetInt());
		}

		if (document.HasMember("EnemyType") && document["EnemyType"].IsInt())	//Checks if the variable exists in .Json file
		{
			_enemyType = (document["EnemyType"].GetInt());
		}
	}


//Constructor
	Boss();


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

	void Attack();
	void Move();
	void MoveNode(bool start = false); // Move using path (toward _destination)
	// FSM
	void FSM();
	void CheckState();

	void ChancePickUps();

	void OnCollision2DTrigger(Collider2D* other);
};