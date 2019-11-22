#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"


void Player::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("WeaponActive") && document["WeaponActive"].IsInt())	//Checks if the variable exists in .Json file
		_weaponActive = document["WeaponActive"].GetInt();
	if (document.HasMember("AmmoRpg") && document["AmmoRpg"].IsInt())	//Checks if the variable exists in .Json file
		_ammoRpg = document["AmmoRpg"].GetInt();
	if (document.HasMember("AmmoTurret") && document["AmmoTurret"].IsInt())	//Checks if the variable exists in .Json file
		_ammoTurret = document["AmmoTurret"].GetInt();
	if (document.HasMember("AmmoWall") && document["AmmoWall"].IsInt())	//Checks if the variable exists in .Json file
		_ammoWall = document["AmmoWall"].GetInt();
	if (document.HasMember("FireratePistol") && document["FireratePistol"].IsDouble())	//Checks if the variable exists in .Json file
		_fireratePistol = document["FireratePistol"].GetDouble();
	if (document.HasMember("FirerateShotgun") && document["FirerateShotgun"].IsDouble())	//Checks if the variable exists in .Json file
		_firerateShotgun = document["FirerateShotgun"].GetDouble();
	if (document.HasMember("FirerateRpg") && document["FirerateRpg"].IsDouble())	//Checks if the variable exists in .Json file
		_firerateRPG = document["FirerateRpg"].GetDouble();
	if (document.HasMember("FirerateTurret") && document["FirerateTurret"].IsDouble())	//Checks if the variable exists in .Json file
		_firerateTurret = document["FirerateTurret"].GetDouble();
	if (document.HasMember("FirerateWall") && document["FirerateWall"].IsDouble())	//Checks if the variable exists in .Json file
		_firerateWall = document["FirerateWall"].GetDouble();
}

void Player::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;
// Logic Data - General
	value.SetInt(_health);
	prototypeDoc.AddMember("Health", value);
	value.Clear();
	value.SetInt(_weaponActive);
	prototypeDoc.AddMember("WeaponActive", value);
	value.Clear();
// Logic Data - Weapons
	value.SetInt(_ammoRpg);
	prototypeDoc.AddMember("AmmoRpg", value);
	value.Clear();
	value.SetInt(_ammoTurret);
	prototypeDoc.AddMember("AmmoTurret", value);
	value.Clear();
	value.SetInt(_ammoWall);
	prototypeDoc.AddMember("AmmoWall", value);
	value.Clear();
	value.SetDouble(_fireratePistol);
	prototypeDoc.AddMember("FireratePistol", value);
	value.Clear();
	value.SetDouble(_firerateShotgun);
	prototypeDoc.AddMember("FirerateShotgun", value);
	value.Clear();
	value.SetDouble(_firerateRPG);
	prototypeDoc.AddMember("FirerateRpg", value);
	value.Clear();
	value.SetDouble(_firerateTurret);
	prototypeDoc.AddMember("FirerateTurret", value);
	value.Clear();
	value.SetDouble(_firerateWall);
	prototypeDoc.AddMember("FirerateWall", value);
	value.Clear();
}

void Player::Inspect()
{
// Logic Data - General
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputInt("WeaponActive ", &_weaponActive);
	ImGui::Spacing();
// Logic Data - Weapons
	ImGui::Spacing();
	ImGui::InputInt("Ammo RPG ", &_ammoRpg);
	ImGui::Spacing();
	ImGui::InputInt("Ammo Turret ", &_ammoTurret);
	ImGui::Spacing();
	ImGui::InputInt("Ammo Wall ", &_ammoWall);
	ImGui::Spacing();
	ImGui::InputDouble("Timer Shoot ", &_timerShoot);
	ImGui::Spacing();
	ImGui::InputDouble("Timer Deploy ", &_timerDeploy);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate Pistol ", &_fireratePistol);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate Shotgun ", &_firerateShotgun);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate RPG ", &_firerateRPG);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate Turret ", &_firerateTurret);
	ImGui::Spacing();
	ImGui::InputDouble("Firerate Wall ", &_firerateWall);
	ImGui::Spacing();
}

Player::Player() :
	_init{ false },
	_camera{ nullptr },
	_health{ 30 },

	_weaponActive{ (int)WeaponId::PISTOL },
	_ammoRpg{ 5 },
	_ammoTurret{ 2 },
	_ammoWall{ 5 },
	_timerShoot{ 0.0 },
	_timerDeploy{ 0.0 },
	_fireratePistol{ 0.1 },
	_firerateShotgun{ 0.5 },
	_firerateRPG{ 2 },
	_firerateTurret{ 5 },
	_firerateWall{ 4 }
{
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

	_timerShoot -= dt;
	_timerDeploy -= dt;

	UpdateInput();
	UpdateCamera();
}

void Player::UpdateCamera()
{
	auto a = EngineSystems::GetInstance()._graphicsSystem;
	a->GetCamera().SetCameraPos(((TransformComponent*)GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos()._x,
		((TransformComponent*)GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetPos()._y);
}

void Player::UpdateInput()
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
		AddForce(GetParentId(), Vector3(0, 1, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
		AddForce(GetParentId(), Vector3(-1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
		AddForce(GetParentId(), Vector3(1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
		AddForce(GetParentId(), Vector3(0, -1, 0), spd);
// MOUSE
	Vector3 aimVector = { // use aimVector to determine direction player is facing
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._x,
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._y,
		0 };
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::MOUSE_LBUTTON))
	{
		WeaponShoot();
	}
// NUMBERS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_1))
	{	// spawn TURRET
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateTurret; // reset timer to frWall
			GameObject* turret = nullptr;
			turret = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::TURRET]);
			// set bullet position & rotation as same as 'parent' obj
			((TransformComponent*)turret->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		}
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_2) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_2))
	{	// spawn WALL
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateWall; // reset timer to frWall
			GameObject* wall = nullptr;
			wall = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
			((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		}
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_3) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_3))
	{	// spawn ENEMY
		GameObject* enemy = nullptr;
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BOSS]);
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
	(_weaponActive != 3) ? ++_weaponActive : _weaponActive = 1; // loop available weapons 1,2,3,1,2,3...
	_timerShoot = 0; // reset timer so can shoot immediately
}

void Player::WeaponShoot()
{
	// 'snap' weapon selection to lowest or highest value
	_weaponActive < 1 ? _weaponActive = 1 : _weaponActive;
	_weaponActive > 3 ? _weaponActive = 3 : _weaponActive;
	if (_timerShoot <= 0)
		switch (_weaponActive)
		{
		case (int)WeaponId::PISTOL:
		{
			WeaponShoot_Pistol();
			break;
		}
		case (int)WeaponId::SHOTGUN:
		{
			WeaponShoot_Shotgun();
			break;
		}
		case (int)WeaponId::RPG:
		{
			if(_ammoRpg)
				WeaponShoot_RPG();
			break;
		}
		default:
			break;
		}
}

void Player::WeaponShoot_Pistol()
{
	_timerShoot = _fireratePistol; // cooldown
	GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	AddForwardForce(bullet->Get_uID(), 70000);
}
void Player::WeaponShoot_Shotgun()
{
	_timerShoot = _firerateShotgun; // cooldown
	Vector3 pos = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	float rot = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate();
	GameObject* bullet = nullptr;
	// 3 bullets, 1 forward, 2 +- 0.2rad
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot);
	AddForwardForce(bullet->Get_uID(), 70000);
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot-0.2f);
	AddForwardForce(bullet->Get_uID(), 70000);
	bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot+0.2f);
	AddForwardForce(bullet->Get_uID(), 70000);
}
void Player::WeaponShoot_RPG()
{
	--_ammoRpg;
	_timerShoot = _firerateRPG; // cooldown
	GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET_T]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	AddForwardForce(bullet->Get_uID(), 70000);
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
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PICK_UPS_HEALTH)
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PICK_UPS));

		_health += 2;
		if (_health > 30)
			_health = 30;
		temp->DestoryThis();
	}
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::PICK_UPS_AMMO)
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PICK_UPS));

		_ammoRpg += 5;
		temp->DestoryThis();
	}
}