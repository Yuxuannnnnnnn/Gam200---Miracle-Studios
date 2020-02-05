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
	if (document.HasMember("ChaseDuration") && document["ChaseDuration"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_chaseDuration = (document["ChaseDuration"].GetDouble());
	}
	if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_attackRangeShoot = document["AttackRangeShoot"].GetDouble();
		_attackRangeShoot *= 100;
		_attackRangeShoot *= _attackRangeShoot;
	}
	if (document.HasMember("AttackRangeMelee") && document["AttackRangeMelee"].IsDouble())	//Checks if the variable exists in .Json file
	{
		_attackRangeMelee = document["AttackRangeMelee"].GetDouble();
		_attackRangeMelee *= 100;
		_attackRangeMelee *= _attackRangeMelee;
	}
}

void Enemy::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{

}

void Enemy::Inspect()
{
	// health, type, stunDur, moveSpd, chaseSpd, atkRange, AtkMelee
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputInt("Enemy Type ", &_enemyType);
	ImGui::Spacing();
	ImGui::InputDouble("Stun Duration ", &_timerStunCooldown);
	ImGui::Spacing();
	ImGui::InputDouble("Move Speed ", &_moveSpeed);
	ImGui::Spacing();
	ImGui::InputDouble("Chase Speed ", &_chaseSpeed);
	ImGui::Spacing();
	ImGui::InputInt("Shoot Attack Range ", &_attackRangeShoot);
	ImGui::Spacing();
	ImGui::InputInt("Melee Attack Range ", &_attackRangeMelee);
	ImGui::Spacing();

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
	_attackRangeShoot{ 0 },
	_attackRangeMelee{ 0 },

	_target{ nullptr },
	_state{ 0 },
	_timerPathing{ 0.0 },
	_timerPathingCooldown{ 0.5 },
	_path{ std::vector<Node*> ()},
	_nextNode{ nullptr },
	_destNode{ nullptr },
	_mapTileSize{ 0 }
{
	_attackRangeMelee = _attackRangeShoot = 100; // _mapTileSize = EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_mapTileSize *= _mapTileSize;
	_attackRangeShoot *= 5; // XxX tileSize
	_attackRangeMelee *= 2;
	_attackRangeShoot *= _attackRangeShoot; // pow(2) for vector3.length() comparison
	_attackRangeMelee *= _attackRangeMelee;
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
// death logic
	if (_health <= 0)
	{
		ChancePickUps(); // currently not working
		GetParentPtr()->SetDestory();
	}

// stunned logic
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

// chase duration logic
	if (_enemyType == 1 && !_stunned)
	{
		if (_state == (int)AiState::ATTACKING)
		{
			_chaseTimer -= dt;
			if (_chaseTimer < 0) // should stun enemy1 when chasing for _chaseDuration
			{
				_chaseTimer = _chaseDuration;
				_stunned = true;
			}
		}
		else
			_chaseTimer = _chaseDuration;
	}

	_timerAttack -= dt;
	_timerPathing -= dt;

	if (_target)
	{
		CheckState();
		FSM();
	}
}

void Enemy::AttackRangeMelee()
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
	{
		_stunned = true;
		_timerAttack = _timerAttackCooldown;
	}
}
void Enemy::AttackRangeShoot()
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

	if (_enemyType == 1 && tempVec3.SquaredLength() < _attackRangeMelee)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(0);
	}
	else if (_enemyType == 2 && tempVec3.SquaredLength() < _attackRangeShoot)
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
			AttackRangeMelee();
		else if (_enemyType == 2)
			AttackRangeShoot();
		else
			;
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
		GameObject* pickups = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Health"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
	else if (Yaya == 8) // ammo
	{
		GameObject* pickups = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Ammo"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
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
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();
	if (otherType.compare("Bullet"))
	{
		_health--;
	}
}