#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"
#include <cstdlib>
#include <ctime>

void Boss::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
	{
		_health = (document["Health"].GetInt());
	}
}

void Boss::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_health);
	prototypeDoc.AddMember("Health", value);
	value.Clear();
}

void Boss::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
}

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
	//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();

	std::unordered_map<size_t, IdentityComponent*> idComList = MyComponentManger._IdentityComponents;
	for (auto& it : idComList)
	{
		if (it.second->GetParentPtr()->Get_uID() >= 1000 && it.second->ObjectType().compare("Player"))
		{
			_target = it.second->GetParentPtr();
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
	return ((TransformComponent*)_target->GetComponent(ComponentId::CT_Transform))->GetPos();
}
Vector3& Boss::GetPosition()
{
	return ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPos();
}

void Boss::Shoot()
{
	// shoot player
	if (_timerAttack <= 0)
	{
		_timerAttack = _timerAttackCooldown;
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
		AddForwardForce(bullet->Get_uID(), 70000);
	}
}

void Boss::Attack()
{
	if (_health > _healthRage) // rotate and shoot
	{
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() += 0.1f;
	// shoot front and back of body
		if (_timerAttack <= 0)
		{
			_timerAttack = _timerAttackCooldown;
			GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() + (const float)PI/2);
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() + (const float)PI);
			AddForwardForce(bullet->Get_uID(), 70000);
			bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() - (const float)PI / 2);
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
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);

		if (_timerAttack <= 0)
		{
			_timerAttack = _timerAttackRageCooldown;
			// spawn bullet
			GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			// set bullet position & rotation as same as 'parent' obj
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 70000);
		}
	}
}

void Boss::ChancePickUps()
{
	std::srand((unsigned)std::time(0));
	int Yaya = 1 + std::rand() % 8;

	if (Yaya == 4) // health
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Health"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
	else if (Yaya == 8) // ammo
	{
		GameObject* pickups = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(MyResourceSystem.GetPrototypeMap()["PickUps_Ammo"]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)pickups->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
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


void Boss::OnCollision2DTrigger(Collider2D* other)
{
	//if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PLAYER || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::TURRET)
	//{
	//	DestoryThis();
	//}
}