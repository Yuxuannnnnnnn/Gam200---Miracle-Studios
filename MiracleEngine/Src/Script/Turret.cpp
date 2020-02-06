#include "PrecompiledHeaders.h"
#include "Script/Turret.h"

Turret::Turret() : 
	_init{ false },
	_health{ 1 }, _healthMax{ 1 },
	_target{ nullptr }, _targetUid{ 0 },
	_state{ (unsigned)AiState::IDLE },
	_timerAttack{ 0.0 }, _timeAttackCooldown{ 3.0 },
	_deployTime{ 0.5 }, _shooting{ false },
	_animState{ 1 }, _animStatePrev{ 1 },
	_transform{nullptr}
	
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
	for (auto& it : GetParentPtr()->GetChildList())
	{
		_turretBase = it.second;
		break;;
	}

	_turretBase->SetEnable(false);


	_transform = ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform));

	Vec3 temp = _transform->GetScaleA();
	_transform->SetScaleA(_deployScale);
	_deployScale = temp;

	// set Deploy animation and set the animation's speed
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Deploy");
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
		_deployTime / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame() );
	// _target = player
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

	if (_deployTime > 0)
	{
		_deployTime -= dt;

		if (_deployTime <= 0.0)
		{
			Vec3 temp = _transform->GetScaleA();
			_transform->SetScaleA(_deployScale);
			_deployScale = temp;
			_turretBase->SetEnable(true);
		}

		return; // force turret to just play animation while "deploying"
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
		return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPositionA();
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
				return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPositionA();
				//break;
			}
		}
	}
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA();

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
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA();
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
			if (it.second == nullptr)
				continue;
			// target searching
			if (!it.second->GetDestory() && (
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
					(((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPositionA()._x - GetPosition()._x),
					(((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPositionA()._y - GetPosition()._y),
					0);
				Vector3 distTemp(
					(((TransformComponent*)it.second->GetComponent(ComponentId::CT_Transform))->GetPositionA()._x - GetPosition()._x),
					(((TransformComponent*)it.second->GetComponent(ComponentId::CT_Transform))->GetPositionA()._y - GetPosition()._y),
					0);
				if (distTarget.SquaredLength() >= distTemp.SquaredLength())
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
			if (itr.second == nullptr)
				continue;
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
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPositionA(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPositionA());
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotationA(
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
	if (id.compare("Player") == 0 ||
		id.compare("player") == 0 || 
		id.compare("Player01") == 0 || 
		id.compare("player01") == 0 )
		_state = (unsigned)AiState::IDLE;
	else
	{
		// check range
		Vector3 tempVec3 = GetDestinationPos() - GetPosition();
		if (tempVec3.SquaredLength() > _attackRangeShoot)
			_state = (unsigned)AiState::MOVING;
		else
			_state = (unsigned)AiState::ATTACKING;
	}
	RotateToTarget();

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		//std::cout << "\t AI No Target!!!\n";
		break;
	case (unsigned)AiState::MOVING:
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