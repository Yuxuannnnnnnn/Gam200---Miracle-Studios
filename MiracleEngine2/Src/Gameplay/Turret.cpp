#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

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
	auto& IdentityComponents = EngineSystems::GetInstance()._gameObjectFactory->GetIdentityComponents();

	for (auto& idPair : IdentityComponents)
	{
		if (idPair.second->GetParentPtr()->Get_uID() >= 1000 && idPair.second->ObjectType().compare("Player"))
		{
			_target = idPair.second->GetParentPtr();
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
		//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
		auto& IdentityComponents = EngineSystems::GetInstance()._gameObjectFactory->GetIdentityComponents();

		for (auto& idPair : IdentityComponents)
		{
			if (idPair.second->GetParentPtr()->Get_uID() >= 1000 && idPair.second->ObjectType().compare("Player"))
			{
				_target = idPair.second->GetParentPtr();
				break;
			}
		}
	}
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

Vector3& Turret::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

void Turret::SearchTarget()
{
	// loop through _listObject, get closest 


	GameObject* tempGO = nullptr, * tempPlayer = nullptr;
	//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();

	std::unordered_map<size_t, IdentityComponent*> idComList = EngineSystems::GetInstance()._gameObjectFactory->GetIdentityComponents();
	for (auto& it : idComList)
	{
		if (it.second->GetParentPtr()->Get_uID() >= 1000 &&
			((it.second->ObjectType().compare("Enemy") || it.second->ObjectType().compare("EnemyTwo")))&&
			!it.second->GetParentPtr()->GetDestory())
		{
			IdentityComponent* idCom = dynamic_cast<IdentityComponent*>(_target->GetComponent(ComponentId::IDENTITY_COMPONENT));

			// check if current target is player
			if (idCom->ObjectType().compare("Player"))
				_target = it.second->GetParentPtr();
		// check distance of both objects
			tempGO = it.second->GetParentPtr();
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
		for (auto& itr : idComList)
			if (itr.second->GetParentPtr()->Get_uID() >= 1000 && itr.second->ObjectType().compare("Player"))
					_target = itr.second->GetParentPtr();
}
void Turret::ShootTarget()
{
	if (_timerAttack <= 0)
	{
		_timerAttack = _timeAttackCooldown;
		//std::cout << "Fired!" << std::endl;
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["Bullet_T"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 50000);
	}
}
void Turret::RotateToTarget()
{
	Vector3 targetVec(
		(GetDestinationPos()._x - GetPosition()._x),
		(GetDestinationPos()._y - GetPosition()._y),
		0
	);
	Vector3 compareVec = { 0, 1, 0 };
	float dot = targetVec._x * compareVec._x + targetVec._y * compareVec._y;
	float det = targetVec._x * compareVec._y - targetVec._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);
}

void Turret::FSM()
{
	SearchTarget();
	// if no enemy
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(_target->GetComponent(ComponentId::IDENTITY_COMPONENT));
	std::string id = IdCom->ObjectType();
	if (id.compare("Player"))
		_state = (unsigned)AiState::IDLE;
	else
	{
		// check range
		Vector3 tempVec3 = GetDestinationPos() - GetPosition();
		if (tempVec3.SquaredLength() > _attackRange)
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