#include "PrecompiledHeaders.h"
#include "Script/Turret.h"

Turret::Turret() : 
	_health{ 1 }, _healthMax{ 1 },
	_target{ nullptr }, _targetUid{ 0 },
	_state{ (unsigned)AiState::IDLE },
	_timerAttack{ 0.0 }, _timeAttackCooldown{ 3.0 },
	_deployTime{ 0.5 }, _shooting{ false },
	_animState{ 1 }, _animStatePrev{ 1 }
	
{
	_attackRangeShoot = 100;// EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
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
	_animState = 1;
	_turretBase->SetEnable(false);

	// set Deploy animation and set the animation's speed
	GetSibilingComponentObject(Animation)->SetEnable(true);
	GetSibilingComponentObject(Animation)->SetCurrentAnimOnce("Deploy");
	GetSibilingComponentObject(Animation)->SetTimeDelay(
		_deployTime / GetSibilingComponentObject(Animation)->GetMaxFrame() );

	GetSibilingComponentObject(Audio)->PlaySFX("Construct");
	// _target = player
	for (auto idPair : _engineSystems._factory->getObjectlist())
	{
		if (GetComponentObject(idPair.second, Identity)->ObjectType().compare("Player") == 0 ||
			GetComponentObject(idPair.second, Identity)->ObjectType().compare("player") == 0 ||
			GetComponentObject(idPair.second, Identity)->ObjectType().compare("Player01") == 0 ||
			GetComponentObject(idPair.second, Identity)->ObjectType().compare("player01") == 0)
		{
			_target = idPair.second;
			_targetUid = idPair.second->Get_uID();
			break;
		}
	}
}

void Turret::LoadResource()
{	
#ifdef LEVELEDITOR
	MyResourceManager.AddNewPrototypeResource({ "BulletT" , MyResourceSystem.GetPrototypeResourcePath("BulletT") });
#endif
}

void Turret::Update(double dt)
{
	if (dt < 0)
		return;

	if (_deployTime > 0)
	{
		_deployTime -= dt;

		if (_deployTime <= 0.0)
		{
			GetSibilingComponentObject(Transform)->SetScaleA(_deployScale);
			GetSibilingComponentObject(Animation)->SetEnable(false);
			GetComponentObject(_turretBase,Transform)->SetPos(GetSibilingComponentObject(Transform)->GetPositionA());

			_turretBase->SetEnable(true);
		}

		return; // force turret to just play animation while "deploying"
	}
	
	_aliveTime -= dt;
	if (_health <= 0 || _aliveTime <= 0)
		GetParentPtr()->SetDestory();

	_timerAttack -= dt;
	FSM();

	// anim updating related logic
	/*if (_init)
		_animState = 1;
	else
		_animState = _shooting ? 2 : 3;*/
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
		return GetComponentObject(_target, Transform)->GetPositionA();
	else
	{
		for (auto idPair : _engineSystems._factory->getObjectlist())
		{
			if (GetComponentObject(idPair.second, Identity)->ObjectType().compare("Player") == 0 ||
				GetComponentObject(idPair.second, Identity)->ObjectType().compare("player") == 0 ||
				GetComponentObject(idPair.second, Identity)->ObjectType().compare("Player01") == 0 ||
				GetComponentObject(idPair.second, Identity)->ObjectType().compare("player01") == 0)
			{
				_target = idPair.second;
				_targetUid = idPair.second->Get_uID();
				return GetComponentObject(_target, Transform)->GetPositionA();
				//break;
			}
		}
	}
	return GetSibilingComponentObject(Transform)->GetPositionA();

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
	return GetSibilingComponentObject(Transform)->GetPositionA();
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
				GetComponentObject(it.second, Identity)->ObjectType().compare("Enemy") == 0 ||
				GetComponentObject(it.second, Identity)->ObjectType().compare("EnemyTwo") == 0
				))
			{
				// if target == player, take first enemy, then continue normal search
				if (GetComponentObject(exist, Identity)->ObjectType().compare("Player") == 0 ||
					GetComponentObject(exist, Identity)->ObjectType().compare("player") == 0 ||
					GetComponentObject(exist, Identity)->ObjectType().compare("Player01") == 0 ||
					GetComponentObject(exist, Identity)->ObjectType().compare("player01") == 0)
				{
					_target = it.second;
					_targetUid = it.second->Get_uID();
				}
				// check distance of both objects
				Vector3 distTarget(
					(GetComponentObject(_target, Transform)->GetPositionA()._x - GetPosition()._x),
					(GetComponentObject(_target, Transform)->GetPositionA()._y - GetPosition()._y),
					0);
				Vector3 distTemp(
					(GetComponentObject(it.second, Transform)->GetPositionA()._x - GetPosition()._x),
					(GetComponentObject(it.second, Transform)->GetPositionA()._y - GetPosition()._y),
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

			IdentityComponent* temp = GetComponentObject(itr.second, Identity);

			if (temp->ObjectType().compare("Enemy") == 0 ||
				temp->ObjectType().compare("EnemyTwo") == 0)
			{
				_targetUid = itr.second->Get_uID();
				_target = itr.second;
				return;
			}
			if (temp->ObjectType().compare("Player") == 0 ||
				temp->ObjectType().compare("player") == 0 ||
				temp->ObjectType().compare("Player01") == 0 ||
				temp->ObjectType().compare("player01") == 0)
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
		GameObject* bullet = CreateObject("BulletT");

		TransformComponent* temp = GetComponentObject(bullet, Transform);
		TransformComponent* myTransform = GetSibilingComponentObject(Transform);
		// set bullet position & rotation as same as 'parent' obj
		temp->SetPos(myTransform->GetPos());
		temp->SetRotate(myTransform->GetRotate());
		AddForwardForce(bullet->Get_uID(), 50000);

		GetSibilingComponentObject(Audio)->PlaySFX("Shoot");
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
	GetSibilingComponentObject(Transform)->GetRotate() = -atan2(det, dot);
}

void Turret::FSM()
{
	SearchTarget();
	// if no enemy
	IdentityComponent* IdCom = GetComponentObject(_target, Identity);
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

void Turret::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = _healthMax = (document["Health"].GetInt());
	if (document.HasMember("Firerate") && document["Firerate"].IsDouble())
		_timeAttackCooldown = (document["Firerate"].GetDouble());

	if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsInt())
	{
		_attackRangeShoot = document["AttackRangeShoot"].GetInt();
		_attackRangeShoot *= 100;
		_attackRangeShoot *= _attackRangeShoot;
	}
	if (document.HasMember("DeployTime") && document["DeployTime"].IsDouble())
		_deployTime = (document["DeployTime"].GetDouble());

	if (document.HasMember("AliveTime") && document["AliveTime"].IsDouble())
		_aliveTime = (document["AliveTime"].GetDouble());

	if (document.HasMember("DeployScale") && document["DeployScale"].IsArray())
	{
		if (document["DeployScale"][0].IsFloat() && document["DeployScale"][1].IsFloat())	//Check the array values
			_deployScale = Vector3{ document["DeployScale"][0].GetFloat(), document["DeployScale"][1].GetFloat(), 1.f };

		if (document["DeployScale"].Size() == 3)
		{
			_deployScale.SetZ(document["DeployScale"][2].GetFloat());
		}
	}
}
//Function Not Needed for scripts
void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetBool(true);
	//prototypeDoc.AddMember("Script2Id", value);
	//
	//value.SetArray();
	//{
	//	rapidjson::Value object;
	//	object.SetObject();
	//	object.AddMember("Health", _healthMax, prototypeDoc.Allocator());
	//	object.AddMember("Firerate", _timeAttackCooldown, prototypeDoc.Allocator());
	//	_attackRangeShoot /= 100;
	//	_attackRangeShoot /= _attackRangeShoot;
	//	object.AddMember("AttackRangeShoot", _attackRangeShoot, prototypeDoc.Allocator());
	//	object.AddMember("DeployTime", _deployTime, prototypeDoc.Allocator());
	//	object.AddMember("AliveTime", _aliveTime, prototypeDoc.Allocator());
	//	value.PushBack(object, prototypeDoc.Allocator());
	//}
}

void Turret::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_healthMax);
	prototypeDoc.AddMember("Health", value, allocator);

	value.SetDouble(_timeAttackCooldown);
	prototypeDoc.AddMember("Firerate", value, allocator);

	int attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
	value.SetInt(attackRangeShoot);
	prototypeDoc.AddMember("AttackRangeShoot", value, allocator);

	value.SetDouble(_deployTime);
	prototypeDoc.AddMember("DeployTime", value, allocator);

	value.SetDouble(_aliveTime);
	prototypeDoc.AddMember("AliveTime", value, allocator);

	value.SetArray();
	{
		for (unsigned i = 0; i < 3; i++)
			value.PushBack(rapidjson::Value(_deployScale[i]).Move(), allocator);
	}
	prototypeDoc.AddMember("DeployScale", value, allocator);


}


void Turret::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	Turret* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), Turret);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value Health;
	rapidjson::Value Firerate;
	rapidjson::Value AttackRangeShoot;
	rapidjson::Value DeployTime;
	rapidjson::Value AliveTime;
	rapidjson::Value DeployScale;

	bool addComponentIntoSceneFile = false;

	if (script->_healthMax != _healthMax)
	{
		addComponentIntoSceneFile = true;
		Health.SetInt(_healthMax);
	}

	if (script->_timeAttackCooldown != _timeAttackCooldown)
	{
		addComponentIntoSceneFile = true;
		Firerate.SetDouble(_timeAttackCooldown);
	}

	if (script->_attackRangeShoot != _attackRangeShoot)
	{
		addComponentIntoSceneFile = true;
		int attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
		AttackRangeShoot.SetInt(attackRangeShoot);
	}

	if (script->_deployTime != _deployTime)
	{
		addComponentIntoSceneFile = true;
		DeployTime.SetDouble(_deployTime);
	}

	if (script->_aliveTime != _aliveTime)
	{
		addComponentIntoSceneFile = true;
		AliveTime.SetDouble(_aliveTime);
	}

	for (int i = 0; i < 3; i++)
	{
		if (script->_deployScale[i] != _deployScale[i])
		{
			addComponentIntoSceneFile = true;
			DeployScale.SetArray();
			for (int i = 0; i < 3; i++)
			{
				DeployScale.PushBack(rapidjson::Value(_deployScale[i]).Move(), allocator);
			}
			break;
		}
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

		if (!Firerate.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("Firerate", Firerate, allocator);
		}

		if (!AttackRangeShoot.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("AttackRangeShoot", AttackRangeShoot, allocator);
		}

		if (!DeployTime.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("DeployTime", DeployTime, allocator);
		}

		if (!AliveTime.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("AliveTime", AliveTime, allocator);
		}

		if (!DeployScale.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("DeployScale", DeployScale, allocator);
		}
	}

}

void Turret::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate ", &_timeAttackCooldown);
	ImGui::Spacing();
	ImGui::InputInt("AttackRange Shoot ", &_attackRangeShoot);
	ImGui::Spacing();
	ImGui::InputDouble("DeployTime ", &_deployTime);
	ImGui::Spacing();
	ImGui::InputDouble("AliveTime ", &_aliveTime);
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::InputFloat2("DeployScale ", _deployScale.m);
	ImGui::Spacing();
}