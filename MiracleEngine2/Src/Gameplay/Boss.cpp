#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"
#include <cstdlib>
#include <ctime>

Boss::Boss() :
	_init {false},
	_health{ 70 },
	_healthRage{ 20 },

	_timerAttack{ 0.0 },
	_timerAttackCooldown{ 0.3 },
	_timerAttackRageCooldown{ 0.7 },

	_target{ nullptr },
	_state{ 1 }
{
}

void Boss::Init()
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
void Boss::Update(double dt)
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

	FSM();

	_timerAttack -= dt;
}

Vector3& Boss::GetDestinationPos()
{
	return ((TransformComponent*)_target->GetComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos();
}
Vector3& Boss::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos();
}

void Boss::Shoot()
{
	// shoot player
	if (_timerAttack <= 0)
	{
		_timerAttack = _timerAttackCooldown;
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 70000);
	}
}

void Boss::Attack()
{
	if (_health > _healthRage) // rotate and shoot
	{
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() += 0.1f;
	// shoot front and back of body
		if (_timerAttack <= 0)
		{
			_timerAttack = _timerAttackCooldown;
			GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() + (const float)PI/2);
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() + (const float)PI);
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() - (const float)PI / 2);
			AddForwardForce(bullet->Get_uID(), 70000);
		}
	}
	else // target player directly
	{
		Vector3 moveVec(
			(GetDestinationPos()._x - GetPosition()._x),
			(GetDestinationPos()._y - GetPosition()._y),
			0);
		// rotate to face player
		Vector3 compareVec = { 0, 1, 0 };
		float dot = moveVec._x * compareVec._x + moveVec._y * compareVec._y;
		float det = moveVec._x * compareVec._y - moveVec._y * compareVec._x;
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

		if (_timerAttack <= 0)
		{
			_timerAttack = _timerAttackRageCooldown;
			// spawn bullet
			GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_E]);
			// set bullet position & rotation as same as 'parent' obj
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 70000);
		}
	}
}

void Boss::FSM()
{
	// Laser with warning(rotate randomly)
	// Aiming at player(got reaction time)
	// Attack pattern base on health
	// 2 states, aimed state, random state

	if (!_target) // if no target
		_state = (unsigned)AiState::IDLE;

	switch (_state)
	{
	case (unsigned)AiState::IDLE:
		//std::cout << "/t AI No Target!!!\n";
		break;
	case (unsigned)AiState::ATTACKING:
	{
		//std::cout << "/t AI ATK!!\n";
		Attack();
		break;
	}
	default:
		break;
	}
}

void Boss::ChancePickUps()
{
	std::srand((unsigned)std::time(0));
	int Yaya = 1 + std::rand() % 8;

	if (Yaya == 4) // health
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::PICK_UPS_HEALTH]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	}
	else if (Yaya == 8) // ammo
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::PICK_UPS_AMMO]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	}

}

void Boss::OnCollision2DTrigger(Collider2D* other)
{
	//if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::TURRET)
	//{
	//	DestoryThis();
	//}
}