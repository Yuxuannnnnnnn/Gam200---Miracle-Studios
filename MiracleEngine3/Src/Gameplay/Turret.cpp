#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Turret::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = (document["Health"].GetInt());
	if (document.HasMember("Firerate") && document["Firerate"].IsDouble())
		_timeAttackCooldown = (document["Firerate"].GetDouble());
	if (document.HasMember("AttackRange") && document["AttackRange"].IsInt())
	{
		_attackRange = (document["AttackRange"].GetInt());
		_attackRange *= (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
		_attackRange *= _attackRange; // pow(2)
	}
}

void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_health);
	prototypeDoc.AddMember("Health", value);
	value.Clear();
	value.SetInt(_timeAttackCooldown);
	prototypeDoc.AddMember("Firerate", value);
	value.Clear();
	value.SetInt(_attackRange);
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
	_state{ (unsigned)AiState::IDLE },
	_timerAttack{ 0.0 },
	_timeAttackCooldown{ 3.0 }
	
{
	_attackRange = (float)EngineSystems::GetInstance()._aiSystem->GetMapTileSize();
	_attackRange *= 5; // 5 tileSize
	_attackRange *= _attackRange; // pow(2)
}

void Turret::Init()
{
	std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
	for (auto it : temp)
	{
		if (it.second->Get_uID() >= 1000 && it.second->GameObjectType() == (unsigned)TypeIdGO::PLAYER)
		{
			_target = it.second;
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
		DestoryThis();

	_timerAttack -= dt;
	FSM();
}

Vector3& Turret::GetDestinationPos()
{
	if (!_target || _target->GetDestory()) // if not target, find player
	{
		std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
		for (auto itr : temp)
			if (itr.second->Get_uID() >= 1000 && itr.second->GameObjectType() == (unsigned)TypeIdGO::PLAYER)
				_target = itr.second;
	}
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

Vector3& Turret::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

void Turret::SearchTarget()
{
	// loop through _listObject, get closest 


	GameObject* tempGO = nullptr, *tempPlayer = nullptr;
	std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
	for (auto itr : temp)
	{
		if (itr.second->Get_uID() >= 1000 &&
			(	(itr.second->GameObjectType() == (unsigned)TypeIdGO::ENEMY) ||
				(itr.second->GameObjectType() == (unsigned)TypeIdGO::ENEMYTWO) ||
				(itr.second->GameObjectType() == (unsigned)TypeIdGO::ENEMYTHREE) ) &&
			!itr.second->GetDestory())	
		{
			// check if current target is player
			if (_target->Get_typeId() == (unsigned)TypeIdGO::PLAYER)
				_target = itr.second;
		// check distance of both objects
			tempGO = itr.second;
			// if _target closer than tempGO,
			Vector3 distTarget(
				(((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._x - GetPosition()._x),
				(((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._y - GetPosition()._y),
				0
			);
			Vector3 distTemp(
				(((TransformComponent*)tempGO->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._x - GetPosition()._x),
				(((TransformComponent*)tempGO->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._y - GetPosition()._y),
				0
			);
			if( distTarget.Length() > distTemp.Length())
				_target = tempGO;
		}
	}
	// else no Enemies detected, so look at player
	if (!tempGO && !_target)
		for (auto itr : temp)
			if (itr.second->Get_uID() >= 1000 && itr.second->GameObjectType() == (unsigned)TypeIdGO::PLAYER)
					_target = itr.second;
}
void Turret::ShootTarget()
{
	if (_timerAttack <= 0)
	{
		_timerAttack = _timeAttackCooldown;
		//std::cout << "Fired!" << std::endl;
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_T]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 50000);
	}
}
void Turret::RotateToTarget()
{
	Vector3 targetVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0);
	Vector3 compareVec = { 0, 1, 0 };
	float dot = targetVec._x * compareVec._x + targetVec._y * compareVec._y;
	float det = targetVec._x * compareVec._y - targetVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);
}

void Turret::FSM()
{
	SearchTarget();
	// if no enemy
	if (_target->Get_uID() == (unsigned)TypeIdGO::PLAYER)
		_state = (unsigned)AiState::IDLE;
	else
	{
		// check range
		Vector3 tempVec3 = GetDestinationPos() - GetPosition();
		if (tempVec3.SquaredLength() > _attackRange)
			_state = (unsigned)AiState::MOVING;
		else if (_target->Get_typeId() == (unsigned)TypeIdGO::PLAYER)
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