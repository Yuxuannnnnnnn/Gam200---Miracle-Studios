#include "PrecompiledHeaders.h"
#include "Script/Turret.h"

void Turret::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = (document["Health"].GetInt());
	if (document.HasMember("Firerate") && document["Firerate"].IsDouble())
		_timeAttackCooldown = (document["Firerate"].GetDouble());
	if (document.HasMember("AttackRange") && document["AttackRange"].IsInt())
	{
		_attackRangeShoot = document["AttackRange"].GetDouble();
		_attackRangeShoot *= 100;
		_attackRangeShoot *= _attackRangeShoot;
	}
}

void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_health);
	prototypeDoc.AddMember("Health", value);
	value.Clear();
	value.SetDouble(_timeAttackCooldown);
	prototypeDoc.AddMember("Firerate", value);
	value.Clear();
	value.SetInt(_attackRangeShoot);
	prototypeDoc.AddMember("AttackRange", value);
	value.Clear();
}

void Turret::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate ", &_timeAttackCooldown);
	ImGui::Spacing();
}

Turret::Turret() : 
	_init{ false },
	_health{ 1 },
	_target{ nullptr },
	_targetUid{ 0 },
	_state{ (unsigned)AiState::IDLE },
	_timerAttack{ 0.0 },
	_timeAttackCooldown{ 3.0 }
	
{
	_attackRangeShoot = EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_attackRangeShoot *= 5; // 5 tileSize
	_attackRangeShoot *= _attackRangeShoot; // pow(2)
}

Turret* Turret::Clone()
{
	return new Turret(*this);
}


void Turret::Init()
{
	for (auto idPair : _engineSystems._factory->getObjectlist())
	{
		if (((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
			((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player01") == 0)
		{
			_target = idPair.second;
			_targetUid = idPair.second->Get_uID();
			break;
		}
	}
}
void Turret::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
	if (_health <= 0)
		GetParentPtr()->SetDestory();

	_timerAttack -= dt;
	FSM();

	// anim updating related logic
	if (_init)
		_animState = 1;
	else
		_animState = _shooting ? 2 : 3;
	// setting animation state
//	if (_animState != _animStatePrev)
//	{
//		_animStatePrev = _animState;
//		if (_animState == 1) // deploy
//			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Deploy");
//		if (_animState == 2) // idle
//			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Idle");
//		if (_animState == 3) // shoot
//			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Shoot");
//	}
}

Vector3& Turret::GetDestinationPos()
{
	GameObject* exist = MyFactory.GetObjectWithId(_targetUid);
	if (exist != nullptr)
		return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos();
	else
	{
		for (auto idPair : _engineSystems._factory->getObjectlist())
		{
			if (((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
				((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0 ||
				((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
				((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player01") == 0)
			{
				_target = idPair.second;
				_targetUid = idPair.second->Get_uID();
				return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos();
				//break;
			}
		}
	}
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPos();

	//if (!_target || _target->GetDestory()) // if not target, find player
	//{
	//	for (auto idPair : _engineSystems._factory->getObjectlist())
	//	{
	//		if (((IdentityComponent*)idPair.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0)
	//		{
	//			_target = idPair.second;
	//			//break;
	//		}
	//	}
	//}
	//return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos();
}

Vector3& Turret::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPos();
}

void Turret::SearchTarget()
{
	GameObject* tempGO = nullptr, * tempPlayer = nullptr;

	//_targetUid, use the factoryList to see if obj still exists, if not then go search for new item
	GameObject* exist = MyFactory.GetObjectWithId(_targetUid);
	if (exist != nullptr)
	{
		for (auto it : _engineSystems._factory->getObjectlist())
		{
			// target searching
			if (it.second->GetAlive() && (
				((IdentityComponent*)it.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Enemy") == 0 ||
				((IdentityComponent*)it.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("EnemyTwo") == 0
				))
			{
				// if target == player, take first enemy, then continue normal search
				if (((IdentityComponent*)exist->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
					((IdentityComponent*)exist->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0 ||
					((IdentityComponent*)exist->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
					((IdentityComponent*)exist->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player01") == 0)
				{
					_target = it.second;
					_targetUid = it.second->Get_uID();
				}
				// check distance of both objects
				Vector3 distTarget(
					(((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos()._x - GetPosition()._x),
					(((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos()._y - GetPosition()._y),
					0);
				Vector3 distTemp(
					(((TransformComponent*)it.second->GetComponent(ComponentId::CT_Transform))->GetPos()._x - GetPosition()._x),
					(((TransformComponent*)it.second->GetComponent(ComponentId::CT_Transform))->GetPos()._y - GetPosition()._y),
					0);
				if (distTarget.Length() > distTemp.Length())
				{
					_targetUid = it.second->Get_uID();
					_target = it.second;
				}
			}
		}
	}
	else
	{
		// just set target to first enemy || player, priority is enemy find 1 enemy
		for (auto itr : _engineSystems._factory->getObjectlist())
		{
			if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Enemy") == 0 ||
				((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("EnemyTwo") == 0)
			{
				_targetUid = itr.second->Get_uID();
				_target = itr.second;
				return;
			}
			if (((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
				((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0 ||
				((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
				((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player01") == 0)
				tempGO = itr.second;
		}
		// target as player
		if (tempGO)
		{
			_targetUid = tempGO->Get_uID();
			_target = tempGO;
		}
	}
}
void Turret::ShootTarget()
{
	if (_timerAttack <= 0)
	{
		_shooting = true;
		_timerAttack = _timeAttackCooldown;
		//std::cout << "Fired!" << std::endl;
			// spawn bullet
		GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletT"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 50000);
	}
	else
		_shooting = false;
}
void Turret::RotateToTarget()
{
	Vector3 targetVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0 );
	Vector3 compareVec = { 0, 1, 0 };
	float dot = targetVec._x * compareVec._x + targetVec._y * compareVec._y;
	float det = targetVec._x * compareVec._y - targetVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);
}

void Turret::FSM()
{
	SearchTarget();
	// if no enemy
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(_target->GetComponent(ComponentId::CT_Identity));
	std::string id = IdCom->ObjectType();
	if (id.compare("Player"))
		_state = (unsigned)AiState::IDLE;
	else
	{
		// check range
		Vector3 tempVec3 = GetDestinationPos() - GetPosition();
		if (tempVec3.SquaredLength() > _attackRangeShoot)
			_state = (unsigned)AiState::MOVING;
		else if (id.compare("Player"))
			_state = (unsigned)AiState::MOVING;
		else
			_state = (unsigned)AiState::ATTACKING;
	}
	RotateToTarget();

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		ShootTarget();
		//std::cout << "\t AI No Target!!!\n";
		break;
	case (unsigned)AiState::MOVING:
		ShootTarget();
		//std::cout << "\t AI MOVING!!\n";
		break;
	case (unsigned)AiState::ATTACKING:
		ShootTarget();
		//std::cout << "\t AI ATK!!\n";
		break;
	default:
		break;
	}
}