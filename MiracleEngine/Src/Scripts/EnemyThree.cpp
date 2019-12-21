#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"
#include <cstdlib>
#include <ctime>

void EnemyThree::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
	{
		_health = (document["Health"].GetInt());
	}
	if (document.HasMember("AttackRange") && document["AttackRange"].IsInt())	//Checks if the variable exists in .Json file
	{
		_attackRange = (document["AttackRange"].GetInt());
		_attackRange *= _mapTileSize;
		//_attackRange *= _attackRange; // pow(2) for vector3.length() comparison
	}
}

void EnemyThree::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{

}

void EnemyThree::Inspect()
{

}

EnemyThree::EnemyThree() :
	_init{ false },
	_health{ 5 },
	_stunned{ false },
	_charging{ false },

	_timerAttack{ 0.0 },
	_timerStun{ 0.0 },
	_timerAttackCooldown{ 1.0 },
	_timerStunCooldown{ 1.0 },
	_attackRange{ 0 },

	_target{ nullptr },
	_state{ 0 },
	_timerPathing{ 0.0 },
	_timerPathingCooldown{ 0.5 },
	_path{ std::vector<Node*> ()},
	_nextNode{ nullptr },
	_destNode{ nullptr },
	_mapTileSize{ 0 }
{
	_attackRange = _mapTileSize = EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_mapTileSize *= _mapTileSize;
}

void EnemyThree::Init()
{
	//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();

	std::unordered_map<size_t, IdentityComponent*> idComList = EngineSystems::GetInstance()._gameObjectFactory->GetIdentityComponents();
	for (auto& it : idComList)
	{
		if (it.second->GetParentPtr()->Get_uID() >= 1000 && it.second->ObjectType().compare("Player"))
		{
			_target = it.second->GetParentPtr();
			break;
		}
	}
}
void EnemyThree::Update(double dt)
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

	if (_charging)
	{
		_timerAttack -= dt;
		if (_timerAttack <= 0)
		{
			_stunned = true;
			_charging = false;
			_timerAttack = _timerAttackCooldown;
		}
		AttackMelee();
		return;
	}

	_timerPathing -= dt;

	CheckState();
	FSM();
}

void EnemyThree::AttackMelee()
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

	AddForwardForce(GetParentId(), 13000);

	// bump into player
	if (_timerAttack <= 0)
		_timerAttack = _timerAttackCooldown;
}

void EnemyThree::CheckState()
{
	// _destinationPos - currPos
	Vector3 tempVec3 = GetDestinationPos() - GetPosition();
	// if (in range)
	if (tempVec3.SquaredLength() < _attackRange)
	{
		_state = (unsigned)AiState::ATTACKING;
		_charging = true;
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
void EnemyThree::FSM()
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
		AttackMelee();
		break;
	}
	default:
		break;
	}
}
void EnemyThree::ChancePickUps()
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

Vector3& EnemyThree::GetDestinationPos()
{
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}
Vector3& EnemyThree::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}
std::vector<Node*>& EnemyThree::GetPath()
{
	return _path;
}
void EnemyThree::Move()
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
void EnemyThree::MoveNode(bool start)
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

int EnemyThree::GetHealth()
{
	return _health;
}
void EnemyThree::SetHealth(int val)
{
	_health = val;
}
void EnemyThree::DecrementHealth()
{
	--_health;
}

void EnemyThree::OnCollision2DTrigger(Collider2D* other)
{
	IdentityComponent* idCom = dynamic_cast<IdentityComponent*>(other->GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));
	if (idCom->ObjectType().compare("Player") || idCom->ObjectType().compare("Turret"))
	{
		_stunned = true;
		_charging = false;
	}
}