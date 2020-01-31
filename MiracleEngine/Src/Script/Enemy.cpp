#include "PrecompiledHeaders.h"
#include "Script/Enemy.h"
#include <cstdlib>
#include <ctime>

void Enemy::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
	{
		_health = (document["Health"].GetInt());
	}
	if (document.HasMember("EnemyType") && document["EnemyType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_enemyType = (document["EnemyType"].GetInt());
	}
	if (document.HasMember("StunDuration") && document["StunDuration"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_timerStunCooldown = (document["StunDuration"].GetDouble());
	}
	if (document.HasMember("MoveSpeed") && document["MoveSpeed"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_moveSpeed = (document["MoveSpeed"].GetDouble());
	}
	if (document.HasMember("ChaseSpeed") && document["ChaseSpeed"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_chaseSpeed = (document["ChaseSpeed"].GetDouble());
	}
	if (document.HasMember("AttackRange") && document["AttackRange"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_attackRange = document["AttackRange"].GetDouble();
		_attackRange *= 100;
		_attackRange *= _attackRange;
	}
	if (document.HasMember("AttackMelee") && document["AttackMelee"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_attackMelee = document["AttackMelee"].GetDouble();
		_attackMelee *= 100;
		_attackMelee *= _attackMelee;
	}
}

void Enemy::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{

}

void Enemy::Inspect()
{

}

Enemy::Enemy() :
	_init{ false },
	_health{ 5 },
	_enemyType{ (int)Enemy_Type::BASIC },

	_stunned{ false },
	_timerStun{ 0.0 },
	_timerStunCooldown{ 2.0 },
	_timerAttack{ 0.0 },
	_timerAttackCooldown{ 1.0 },
	_attackRange{ 0 },
	_attackMelee{ 0 },

	_target{ nullptr },
	_state{ 0 },
	_timerPathing{ 0.0 },
	_timerPathingCooldown{ 0.5 },
	_path{ std::vector<Node*> ()},
	_nextNode{ nullptr },
	_destNode{ nullptr },
	_mapTileSize{ 0 }
{
	_attackMelee = _attackRange = 100; // _mapTileSize = EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_mapTileSize *= _mapTileSize;
	_attackRange *= 5; // XxX tileSize
	_attackMelee *= 2;
	_attackRange *= _attackRange; // pow(2) for vector3.length() comparison
	_attackMelee *= _attackMelee;
}

Enemy* Enemy::Clone()
{
	return new Enemy(*this);
}

void Enemy::Init()
{
	for (auto itr : _engineSystems._factory->getObjectlist())
	{
		if ( ( ((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01")==0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0) &&
			(((LogicComponent*)itr.second->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)) &&
			!itr.second->GetDestory()
			)
		{
			_target = itr.second;
			break;
		}
	}
}
void Enemy::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}

	if (_health <= 0)
	{
		ChancePickUps();
		GetParentPtr()->SetDestory();
	}

	if (_stunned)
	{
		_timerStun -= dt;
		if (_enemyType == 1)
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() + 0.1 );
		if (_enemyType == 2)
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() - 0.1 );
		if (_timerStun <= 0)
		{
			_timerStun = _timerStunCooldown;
			_stunned = false;
		}
		return;
	}

	_timerAttack -= dt;
	_timerPathing -= dt;

	if (_target)
	{
		CheckState();
		FSM();
	}
}

void Enemy::AttackMelee()
{
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0
	);

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);
			//moveVec.Normalize();
			//moveVec *= spd;
			//((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetPos(
			//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos() + moveVec
			//);
	AddForwardForce(GetParentId(), 1000 * _chaseSpeed);

	// bump into player
	if (_timerAttack <= 0)
		_timerAttack = _timerAttackCooldown;
}
void Enemy::AttackRange()
{
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0
	);

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);

	// shoot player
	if (_timerAttack <= 0)
	{
		_timerAttack = _timerAttackCooldown;
		// spawn bullet
		GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 70000);
	}
}
void Enemy::CheckState()
{
	// _destinationPos - currPos
	Vector3 tempVec3 = GetDestinationPos() - GetPosition();

	if (_enemyType == 1 && tempVec3.SquaredLength() < _attackMelee)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(0);
	}
	else if (_enemyType == 2 && tempVec3.SquaredLength() < _attackRange)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(0);
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		// set Anim state to EyeWhite
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(1);
	}
}
void Enemy::FSM()
{
	if (!_target) // if no target
		_state = (unsigned)AiState::IDLE;

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		//std::cout << "/t AI No Target!!!\n";
		break;
	case (unsigned)AiState::MOVING:
	{
		Vector3 moveVec(
			(GetDestinationPos()._x - GetPosition()._x),
			(GetDestinationPos()._y - GetPosition()._y),
			0
		);

		// rotate to face player
		Vector3 compareVec = { 0, 1, 0 };
		float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
		float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);
				//moveVec.Normalize();
				//moveVec *= spd;
				//((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetPos(
				//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos() + moveVec
				//);
		AddForwardForce(GetParentId(), 1000 * _moveSpeed);
		//std::cout << "/t AI Move!!!\n";
	// get pathfinding
		//if (_timerPathing > 0)
		//{
		//	MoveNode();
		//}
		//else
		//{
		//	std::vector<Node*> newPath = EngineSystems::GetInstance()._aiSystem->PathFinding(GetPosition(), GetDestinationPos());
		//	if (!_destNode || _destNode->GetNodeId() != newPath.back()->GetNodeId())
		//	{
		//		_path = newPath;
		//		_nextNode = _path.front();
		//		_destNode = _path.back();
		//		MoveNode(true);
		//	}
		//	else
		//		MoveNode();
		//	_timerPathing = _timerPathingCooldown;
		//}
		break;
	}
	case (unsigned)AiState::ATTACKING:
	{
		//std::cout << "/t AI ATK!!\n";
		if (_enemyType == 1)
			AttackMelee();
		else if (_enemyType == 2)
			AttackRange();
		else
			;
	}
	default:
		break;
	}
}
void Enemy::ChancePickUps()
{
	//std::srand((unsigned)std::time(0));
	//int Yaya = 1 + std::rand() % 8;

	//if (Yaya == 4) // health
	//{
	//	GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Health"]);
	//	// set bullet position & rotation as same as 'parent' obj
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	//}
	//else if (Yaya == 8) // ammo
	//{
	//	GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Ammo"]);
	//	// set bullet position & rotation as same as 'parent' obj
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	//}
}

Vector3& Enemy::GetDestinationPos()
{
	if (_target)
		return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos();
}
Vector3& Enemy::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPos();
}
std::vector<Node*>& Enemy::GetPath()
{
	return _path;
}
void Enemy::Move()
{ // move directly to Target.Pos
	const float spd = 4.f;
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0
	);

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);

	AddForwardForce(GetParentId(), 12000);
}
void Enemy::MoveNode(bool start)
{ // move to NextNod
							//std::cout << _nextNode->GetNodeId() << std::endl << std::endl;

// TODO : Check if in range of nextNode, then pop front of list and assign nextNode;

	float spd = 4.f;
	Vector3 moveVec(
		(_nextNode->GetPosition()._x - GetPosition()._x),
		(_nextNode->GetPosition()._y - GetPosition()._y),
		0);

	// check if should get the nextNextNode
	unsigned mapTileSize = 10 * 10;// next time is get the map size from AiComponent or sth

	if (start)
		mapTileSize = 100 * 100;

	if (moveVec.SquaredLength() < mapTileSize)
	{
		if (_path.size() > 1)
		{
			Node* nextNextNode = *(++(_path.begin())); // get node after
			if (nextNextNode)
			{
				moveVec = Vector3(
					(nextNextNode->GetPosition()._x - GetPosition()._x),
					(nextNextNode->GetPosition()._y - GetPosition()._y),
					0
				);
				_nextNode = nextNextNode;
				//_path = EngineSystems::GetInstance()._aiSystem->PathFinding(GetPosition(), GetDestinationPos());
				_path.erase(_path.begin());
			}
			else
				_state = (unsigned)AiState::ATTACKING;
		}
	}

	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);

	// move towards node
	moveVec.Normalize();

	moveVec *= (spd);
	//std::cout << moveVec._x << " " << moveVec._y << std::endl;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos() += moveVec;
}

int Enemy::GetHealth()
{
	return _health;
}
void Enemy::SetHealth(int val)
{
	_health = val;
}
void Enemy::DecrementHealth()
{
	--_health;
}
void Enemy::SetStunned()
{
	_stunned = true;
}

void Enemy::OnCollision2DTrigger(Collider2D* other)
{
	//if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::TURRET)
	//{
	//	DestoryThis();
	//}
}