#include "PrecompiledHeaders.h"
#include "Script/Enemy.h"
#include <cstdlib>
#include <ctime>
#include "EntrancePortal.h"

Enemy::Enemy() :
	_health{ 5 },
	_enemyType{ (int)Enemy_Type::BASIC },

	_stunned{ false }, _stunActivate{ false },
	_timerStun{ 0.0 }, _timerStunCooldown{ 2.0 },
	_timerAttack{ 0.0 }, _timerAttackCooldown{ 1.0 },
	_attackRangeShoot{ 0 }, _attackRangeMelee{ 0 },
	_moveSpeed{ 0.0 }, _chaseSpeed{ 0.0 },
	_chaseTimer{ 0.0 }, _chaseDuration{ 0.0 },

	_timerDeath{ 0.0 }, _dt{ 0.0 }, hitTintTimer{ 0.0 }, hitTintDuration{ 0.3 },
	_deathStart{ false }, _redTint{ false }, _justHit{ false },
	_charging{ false }, _chargingStart{false},
	_animState{ 1 }, _animStatePrev{ 1 },

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

void Enemy::ForceDeath()
{
	_deathStart = true; _timerDeath = 1;
	GetSibilingComponent(ComponentId::CT_CircleCollider2D);// ->SetEnable(false);
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Death");
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(true);
	GetSibilingComponentObject(RigidBody2D)->SetEnable(false);
	return;
}

void Enemy::OnHit()
{
	if (_justHit)
	{
		_justHit = false;
		_health--;
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("Hit");
		if (_redTint)
			hitTintTimer = hitTintDuration;
		else
		{
			_redTint = true;
			GetSibilingComponentObject(Graphic)->SetTintColor(glm::vec4(0.3, 0.3, 0, 0)); // set tint red
		}
	}
	if (_redTint)
	{
		hitTintTimer -= _dt;
		if (hitTintTimer > 0)
			return;
		else
		{
			_redTint = false;
			GetSibilingComponentObject(Graphic)->SetTintColor(glm::vec4(0, 0, 0, 0)); // set tint normal
		}
	}
	else
		hitTintTimer = hitTintDuration;
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
			(((LogicComponent*)itr.second->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)))
		{
			_target = itr.second;
			break;
		}
	}
	_animState = 1;
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Move");
}

void Enemy::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewPrototypeResource({ "BulletE" , MyResourceSystem.GetPrototypeResourcePath("BulletE") });
	MyResourceManager.AddNewPrototypeResource({ "PickUps_Health" , MyResourceSystem.GetPrototypeResourcePath("PickUps_Health") });
	MyResourceManager.AddNewPrototypeResource({ "PickUps_Ammo" , MyResourceSystem.GetPrototypeResourcePath("PickUps_Ammo") });
#endif
}

void Enemy::Update(double dt)
{
	if (dt < 0)
		return;
	_dt = dt;
// death logic
	if (_timerDeath)
	{
		// if animation finish playing
		if (_timerDeath > 0 && !((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
		{
			//GetParentPtr()->SetEnable(false);
			((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetEnable(false);
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(false);
			ChancePickUps();

			std::string temp = "EntrancePortal";
			((EntrancePortal*)MyLogicSystem.GetScriptList()[((LogicComponent*)(MyFactory.GetLinkIDObject(1239)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]])->IncreaseKillCount(1);
			GetParentPtr()->SetDestory();
		}
		return;
	}
	if (_health <= 0)
	{
		_timerDeath += dt;

		if (!_deathStart)
		{
			_deathStart = true;
			GetSibilingComponent(ComponentId::CT_CircleCollider2D)->SetEnable(false);
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Death");
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(true);
			GetSibilingComponentObject(RigidBody2D)->SetEnable(false);
			AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
			audcom->PlaySFX("Death");
		}
	}
	OnHit();
// stunned logic
	if (_stunActivate && _health > 0)
	{
		_stunned = true;
		_stunActivate = false;
		_timerStun = _timerStunCooldown;
		if (_enemyType == 1)
		{
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Move");
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(false);
		}
	}
	if (_stunned && _health>0)
	{
		_timerStun -= dt;
		//if (_enemyType == 1)
		//((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(
		//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() + 0.1 );
		//if (_enemyType == 2)
		//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(
		//	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() - 0.1 );
		if (_timerStun < 0)
		{
			_stunned = false;
			_animState = _animStatePrev = 1;
		}
		else
			return;
	}



	_timerAttack -= dt;
	_timerPathing -= dt;

	if (_health > 0 && _target)
	{
		CheckState();
		FSM(dt);
	}

// anim updating related logic
	if (_enemyType == 1)
		_animState = _charging ? 2 : 1;
// setting animation state
	if (_animState != _animStatePrev)
	{
		_animStatePrev = _animState;

		if (_enemyType == 1) // charger
		{			
			if (_animState == 1) // moving
			{
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(false);
			}
			if (_animState == 2) // charging
			{
				AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
				audcom->PlaySFX("charging");
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(true);
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Move");
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
					_chaseDuration / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame());
			}
		}
		if (_enemyType == 2) // shooter
		{

			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Move");
			//if (_animState == 1) // moving
			//	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Move");
			//else
			//	return;
		}
	}
	else
		_animStatePrev = _animState;

	// charging duration logic
	if (_enemyType == 1 && _health > 0 && _charging)
	{
		if (((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
		{
			_chaseTimer -= dt;
		}
		else
		{
			_chaseTimer = _chaseDuration;
			_charging = false;
			SetStunned();
		}
	}
}

void Enemy::AttackRangeMelee(double dt)
{
	_charging = true;
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0);
	// rotate to face player
	Vector3 compareVec = { 0, 1, 0 };
	float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
	float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);
	AddForwardForce(GetParentId(), 100000 * _chaseSpeed * dt);
}
void Enemy::AttackRangeShoot()
{
	Vector3 moveVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0);

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
		GameObject* bullet = CreateObject("BulletE");
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 70000);

		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("shoot");
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
		//((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(0);
	}
	else if (_enemyType == 2 && tempVec3.SquaredLength() < _attackRangeShoot)
	{
		_state = (unsigned)AiState::ATTACKING;
		// set Anim state to EyeRed
		//((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(0);
	}
	else
	{
		_state = (unsigned)AiState::MOVING;
		// set Anim state to EyeWhite
		//((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetTextureState(1);
	}
}
void Enemy::FSM(double dt)
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
			0);

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
		AddForwardForce(GetParentId(), 100000 * _moveSpeed * dt);
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
		{
			Vector3 distVec(
				(GetDestinationPos()._x - GetPosition()._x),
				(GetDestinationPos()._y - GetPosition()._y),
				0);
			if (distVec.SquaredLength() < _attackRangeMelee)
				AttackRangeMelee(dt);
		}
		if (_enemyType == 2)
		{
			Vector3 distVec(
				(GetDestinationPos()._x - GetPosition()._x),
				(GetDestinationPos()._y - GetPosition()._y),
				0);
			if (distVec.SquaredLength() < _attackRangeShoot)
				AttackRangeShoot();
		}
	}
	default:
		break;
	}
}
void Enemy::ChancePickUps()
{
	std::srand((unsigned)std::time(0));
	int Yaya = (1 + std::rand()) % 10;

	//if (Yaya <= 2) // health 40%drop
	if (Yaya <= 4) // 40%
	{
		GameObject* pickups = CreateObject("PickUps_Health");
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
	//else if (Yaya == 3 || Yaya == 4) // ammo 20%drop
	//{
	//	GameObject* pickups = CreateObject("PickUps_Ammo");
	//	// set bullet position & rotation as same as 'parent' obj
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	//	((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	//}
}

Vector3 Enemy::GetDestinationPos()
{
	if (_target)
		return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPositionA();
	else
		return Vector3();
}
Vector3 Enemy::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA();
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
		0);

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
					0);
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
	_stunActivate = true;
}

void Enemy::OnCollision2DTrigger(Collider2D* other)
{
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();
	if (otherType.compare("Bullet") == 0 || otherType.compare("BulletE") == 0 || otherType.compare("BulletT") == 0)
	{
		_justHit = true;
		SetStunned();
		AddForwardForce(GetParentId(), -150000);
	}
	if (otherType.compare("Player") == 0 || otherType.compare("player") == 0 || otherType.compare("PlayerShield") == 0)
	{
		_stunActivate = true;
		_timerAttack = _timerAttackCooldown;
		AddForwardForce(GetParentId(), -150000);
	}
}


void Enemy::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
	{
		_health = (document["Health"].GetInt());
	}
	if (document.HasMember("EnemyType") && document["EnemyType"].IsInt())
	{
		_enemyType = (document["EnemyType"].GetInt());
	}
	if (document.HasMember("StunDuration") && document["StunDuration"].IsDouble())
	{
		_timerStunCooldown = (document["StunDuration"].GetDouble());
	}
	if (document.HasMember("MoveSpeed") && document["MoveSpeed"].IsDouble())
	{
		_moveSpeed = (document["MoveSpeed"].GetDouble());
	}
	if (document.HasMember("ChaseSpeed") && document["ChaseSpeed"].IsDouble())
	{
		_chaseSpeed = (document["ChaseSpeed"].GetDouble());
	}
	if (document.HasMember("ChaseDuration") && document["ChaseDuration"].IsDouble())
	{
		_chaseDuration = (document["ChaseDuration"].GetDouble());
	}
	if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsDouble())
	{
		_attackRangeShoot = (int)document["AttackRangeShoot"].GetDouble();
		_attackRangeShoot *= 100;
		_attackRangeShoot *= _attackRangeShoot;
	}
	if (document.HasMember("AttackRangeMelee") && document["AttackRangeMelee"].IsDouble())
	{
		_attackRangeMelee = (int)document["AttackRangeMelee"].GetDouble();
		_attackRangeMelee *= 100;
		_attackRangeMelee *= _attackRangeMelee;
	}
}
//No Need this function
void Enemy::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void Enemy::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_health);
	prototypeDoc.AddMember("Health", value, allocator);

	value.SetInt(_enemyType);
	prototypeDoc.AddMember("EnemyType", value, allocator);

	value.SetDouble(_timerStunCooldown);
	prototypeDoc.AddMember("StunDuration", value, allocator);

	value.SetDouble(_moveSpeed);
	prototypeDoc.AddMember("MoveSpeed", value, allocator);

	value.SetDouble(_chaseSpeed);
	prototypeDoc.AddMember("ChaseSpeed", value, allocator);

	value.SetDouble(_chaseDuration);
	prototypeDoc.AddMember("ChaseDuration", value, allocator);


	double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
	value.SetDouble(attackRangeShoot);
	prototypeDoc.AddMember("AttackRangeShoot", value, allocator);

	double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
	value.SetDouble(attackRangeMelee);
	prototypeDoc.AddMember("AttackRangeMelee", value, allocator);

}

void Enemy::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	Enemy* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), Enemy);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value Health;
	rapidjson::Value EnemyType;
	rapidjson::Value StunDuration;
	rapidjson::Value MoveSpeed;
	rapidjson::Value ChaseSpeed;
	rapidjson::Value ChaseDuration;
	rapidjson::Value AttackRangeShoot;
	rapidjson::Value AttackRangeMelee;

	bool addComponentIntoSceneFile = false;


	if (script->_health != _health)
	{
		addComponentIntoSceneFile = true;
		Health.SetInt(_health);
	}

	if (script->_enemyType != _enemyType)
	{
		addComponentIntoSceneFile = true;
		EnemyType.SetInt(_enemyType);
	}

	if (script->_timerStunCooldown != _timerStunCooldown)
	{
		addComponentIntoSceneFile = true;
		StunDuration.SetDouble(_timerStunCooldown);
	}

	if (script->_moveSpeed != _moveSpeed)
	{
		addComponentIntoSceneFile = true;
		MoveSpeed.SetDouble(_moveSpeed);
	}

	if (script->_chaseSpeed != _chaseSpeed)
	{
		addComponentIntoSceneFile = true;
		ChaseSpeed.SetDouble(_chaseSpeed);
	}

	if (script->_chaseDuration != _chaseDuration)
	{
		addComponentIntoSceneFile = true;
		ChaseDuration.SetDouble(_chaseDuration);
	}

	if (script->_attackRangeShoot != _attackRangeShoot)
	{
		addComponentIntoSceneFile = true;

		double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
		AttackRangeShoot.SetDouble(attackRangeShoot);
	}

	if (script->_attackRangeMelee != _attackRangeMelee)
	{
		addComponentIntoSceneFile = true;

		double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
		AttackRangeMelee.SetDouble(attackRangeMelee);
	}

	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		if (!Health.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Health", Health, allocator);
		}

		if (!EnemyType.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("EnemyType", EnemyType, allocator);
		}

		if (!StunDuration.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("StunDuration", StunDuration, allocator);
		}


		if (!MoveSpeed.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("MoveSpeed", MoveSpeed, allocator);
		}


		if (!ChaseSpeed.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("ChaseSpeed", ChaseSpeed, allocator);
		}


		if (!ChaseDuration.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("ChaseDuration", ChaseDuration, allocator);
		}


		if (!AttackRangeShoot.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("AttackRangeShoot", AttackRangeShoot, allocator);
		}

		if (!AttackRangeMelee.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("AttackRangeMelee", AttackRangeMelee, allocator);
		}
	}
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