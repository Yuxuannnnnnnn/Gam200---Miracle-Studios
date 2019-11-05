#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

Player::Player()
{
	_health = 30;
	_weaponActive = 1;
	_timer = 0;
	_timerCooldown = 1;
}

void Player::Update(double dt)
{
	_timer -= dt;
	updateInput();
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
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._x - ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos()._x,
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._y - ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos()._y,
		0 };
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON))
	{	// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
	}
// NUMBERS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1))
	{	
		if (_timer <= 0)
			WeaponShoot();
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
	switch (_weaponActive)
	{
	case (int)WeaponId::PISTOL:
		WeaponShoot_Pistol();
		break;
	case (int)WeaponId::SHOTGUN:
		break;
	case (int)WeaponId::RPG:
		break;
	}
}

void Player::WeaponShoot_Pistol()
{
	GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
}
void Player::WeaponShoot_Shotgun()
{

}
void Player::WeaponShoot_RPG()
{

}


int Player::GetHealth()
{
	return _health;
}
void Player::SetHealth(int val)
{
	_health = val;
}
