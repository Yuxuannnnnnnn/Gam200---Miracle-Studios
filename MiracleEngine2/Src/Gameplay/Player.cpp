#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Player::Player()
{
	_init = false;
	_health = 30;
	_weaponActive = 2;
	_rpgAmmo = 0;
	_timer = 0;
	_timerCooldown = 0.5;
	_camera = nullptr;
}

void Player::Init()
{
	// find Camera
	std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();
	for (auto it : temp)
	{
		if (it.second->Get_uID() >= 1000 && it.second->GameObjectType() == (unsigned)TypeIdGO::CAMERA)
		{
			_camera = it.second;
			break;
		}
	}
}

void Player::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
	_timer -= dt;

	updateInput();
	UpdateCamera();
}

void Player::UpdateCamera()
{
	auto a = EngineSystems::GetInstance()._graphicsSystem;
	a->GetCamera().SetCameraPos(((TransformComponent*)GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos()._x,
		((TransformComponent*)GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos()._y);
}

void Player::updateInput()
{
 //OTHERS
	//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
	//	_InputStyle = INGAME_PAUSE_ESCAPE;
// SCALE
	Vector3 scaleVec = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale();
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
		scaleVec._x -= 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
		scaleVec._x += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_UP))
		scaleVec._y += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
		scaleVec._y -= 1;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->SetScale(scaleVec);
// MOVEMENT
	float spd = 5.f * 10000; // get spd
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_W))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(0, 1, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(-1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(0, -1, 0), spd);
// MOUSE

	Vector3 aimVector = { // use aimVector to determine direction player is facing
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._x,
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._y,
		0 };
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON))
	{
		WeaponShoot();
	}
// NUMBERS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1))
	{	// spawn TURRET
		GameObject* turret = nullptr;
		turret = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::TURRET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)turret->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_2))
	{	// spawn WALL
		GameObject* wall = nullptr;
		wall = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
		((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_3))
	{	// spawn ENEMY
		GameObject* enemy = nullptr;
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMYTWO]);
		((TransformComponent*)enemy->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(Vector3(0, 0, 0));
	}
// KEYS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_Q))
	{	
		WeaponSwitch();
	}
}

void Player::WeaponSwitch()
{
	(_weaponActive != 3) ? ++_weaponActive : _weaponActive = 1;
}

void Player::WeaponShoot()
{
	if (_timer <= 0)
		switch (_weaponActive)
		{
		case (int)WeaponId::PISTOL:
			WeaponShoot_Pistol();
			break;
		case (int)WeaponId::SHOTGUN:
			WeaponShoot_Shotgun();
			break;
		case (int)WeaponId::RPG:
		{
			if(_rpgAmmo)
				WeaponShoot_RPG();
		}
		break;
		}
}

void Player::WeaponShoot_Pistol()
{
	_timer = 0.2; // cooldown
	GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
}
void Player::WeaponShoot_Shotgun()
{
	_timer = 0.7; // cooldown
	Vector3 pos = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	float rot = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate();
	GameObject* bullet = nullptr;
	// 3 bullets, 1 forward, 2 +- 0.2rad
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot);
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot-0.2f);
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot+0.2f);
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
}
void Player::WeaponShoot_RPG()
{
	--_rpgAmmo;
	_timer = 2; // cooldown
	GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_T]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
}


int Player::GetHealth()
{
	return _health;
}
void Player::SetHealth(int val)
{
	_health = val;
}

void Player::OnTrigger2DEnter(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PICK_UPS_AMMO || other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PICK_UPS_HEALTH)
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PICK_UPS));

		if (temp->_pickupType == (int)PickUp_Type::HEALTH_REGAN)
		{
			_health += 2;
			if (_health > 30)
				_health = 30;
		}
		else if (temp->_pickupType == (int)PickUp_Type::ROCKET_AMMO)
		{
			_rpgAmmo = 5;
		}
			
	}
}