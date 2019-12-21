#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"
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
	if (document.HasMember("AttackRange") && document["AttackRange"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_attackRange = (document["AttackRange"].IsDouble());
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
	_attackMelee = _attackRange = _mapTileSize = EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_mapTileSize *= _mapTileSize;
	_attackRange *= 5; // XxX tileSize
	_attackMelee *= 2;
	_attackRange *= _attackRange; // pow(2) for vector3.length() comparison
	_attackMelee *= _attackMelee;
}

void Enemy::Init()
{
	//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
	auto& IdentityComponents = EngineSystems::GetInstance()._gameObjectFactory->GetIdentityComponents();
	
	for (auto& idPair : IdentityComponents)
	{
		if (idPair.second->GetParentPtr()->Get_uID() >= 1000 && (idPair.second->ObjectType().compare("Player") == 0))
		{
			_target = idPair.second->GetParentPtr();
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
		DestoryThis();
	}

	if (_stunned)
	{
		_timerStun -= dt;
		if (_timerStun <= 0)
		{
			_timerStun = _timerStunCooldown;
			_stunned = false;
		}
		return;
	}

	_timerAttack -= dt;
	_timerPathing -= dt;

	CheckState();
	FSM();
}

void Enemy::AttackMelee()
{
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
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	AddForwardForce(GetParentId(), 6000);

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
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	// shoot player
	if (_timerAttack <= 0)
	{
		_timerAttack = _timerAttackCooldown;
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["BulletE"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 70000);
	}
}
void Enemy::CheckState()
{
	// _destinationPos - currPos
	Vector3 tempVec3 = GetDestinationPos() - GetPosition();
	// if (in range)
	if (tempVec3.SquaredLength() < _attackRange)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::GRAPHICS_COMPONENT))->SetTextureState(0);
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		// set Anim state to EyeWhite
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::GRAPHICS_COMPONENT))->SetTextureState(1);
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
		//std::cout << "/t AI Move!!!\n";
	// get pathfinding
		if (_timerPathing > 0)
		{
			MoveNode();
		}
		else
		{
			std::vector<Node*> newPath = EngineSystems::GetInstance()._aiSystem->PathFinding(GetPosition(), GetDestinationPos());
			if (!_destNode || _destNode->GetNodeId() != newPath.back()->GetNodeId())
			{
				_path = newPath;
				_nextNode = _path.front();
				_destNode = _path.back();
				MoveNode(true);
			}
			else
				MoveNode();
			_timerPathing = _timerPathingCooldown;
		}
		break;
	}
	case (unsigned)AiState::ATTACKING:
	{
		//std::cout << "/t AI ATK!!\n";
		if (_enemyType == (int)Enemy_Type::BASIC)
			AttackMelee();
		else
			AttackRange();
		break;
	}
	default:
		break;
	}
}
void Enemy::ChancePickUps()
{
	std::srand((unsigned)std::time(0));
	int Yaya = 1 + std::rand() % 8;

	if (Yaya == 4) // health
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["PickUps_Health"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	}
	else if (Yaya == 8) // ammo
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["PickUps_Ammo"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	}
}

Vector3& Enemy::GetDestinationPos()
{
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}
Vector3& Enemy::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
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
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	AddForwardForce(GetParentId(), 6000);
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
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	// move towards node
	moveVec.Normalize();

	moveVec *= (spd);
	//std::cout << moveVec._x << " " << moveVec._y << std::endl;
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos() += moveVec;
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