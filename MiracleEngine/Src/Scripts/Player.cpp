#include "PrecompiledHeaders.h"


void Player::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
		_health = _healthMax = document["Health"].GetInt();
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
	ImGui::InputInt("HealthMax ", &_healthMax);
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
	_god{ false },
	_init{ false },
	_camera{ nullptr },
	_health{ 30 }, _healthMax{ 30 },
	_progress{ 0 }, _progressMax{ 30 },

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
	_firerateWall{ 4 },
	_timerProg{ 0.0 }, _timerProgCooldown{ 1.0 }
{
}

void Player::Init()
{
	// find Camera
	//std::unordered_map<size_t, GameObject*> temp = _GlobalContainer._gameObjectFactory->getObjectlist();

	std::unordered_map<size_t, IdentityComponent*> IdComList = _GlobalContainer._gameObjectFactory->GetIdentityComponents();

	for (auto& idPair : IdComList)
	{
		if (idPair.second->GetParentPtr()->Get_uID() >= 1000 && idPair.second->ObjectType().compare("Camera"))
		{
			_camera = idPair.second->GetParentPtr();
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
	if (_god)
	{
		_health = _healthMax;
		_ammoRpg = _ammoTurret = _ammoWall = 10;
		_timerShoot = _timerDeploy = 0.0;
	}

	_timerShoot -= dt;
	_timerDeploy -= dt;
	_timerProg -= dt;

	UpdateInput();
	UpdateCamera();
	UpdateUI();
}

void Player::UpdateCamera()
{
	auto a = _GlobalContainer._graphicsSystem;
	/*a->GetCamera().SetCameraPos(((TransformComponent*)GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._x,
		((TransformComponent*)GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT))->GetPos()._y);*/
}

void Player::UpdateUI()
{
	if (_timerProg <= 0)
	{
		_timerProg = _timerProgCooldown;
		ProgressIncement();
	}
	if (_progress == _progressMax)
	{
		_progress = 0;
		_progressMax *= 2;
	}
	// set percents
	//_GlobalContainer._graphicsSystem->SetHealthPercentage(static_cast<float>(_health) / _healthMax);
	//_GlobalContainer._graphicsSystem->SetProgressPercentage(static_cast<float>(_progress) / _progressMax);
}

void Player::UpdateInput()
{
 //OTHERS
	//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
	//	_InputStyle = INGAME_PAUSE_ESCAPE;
// SCALE
	Vector3 scaleVec = ((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetScale();
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
		scaleVec._x -= 1;
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
		scaleVec._x += 1;
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_UP))
		scaleVec._y += 1;
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
		scaleVec._y -= 1;
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->SetScale(scaleVec);
// MOVEMENT
	float spd = 3.f * 10000; // get spd
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_W))
		AddForce(GetParentId(), Vector3(0, 1, 0), spd);
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_A))
		AddForce(GetParentId(), Vector3(-1, 0, 0), spd);
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_D))
		AddForce(GetParentId(), Vector3(1, 0, 0), spd);
	if (_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_S))
		AddForce(GetParentId(), Vector3(0, -1, 0), spd);
// MOUSE
	Vector3 aimVector = { // use aimVector to determine direction player is facing
		_GlobalContainer._inputSystem->GetMousePos()._x,
		_GlobalContainer._inputSystem->GetMousePos()._y,
		0 };
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::MOUSE_LBUTTON))
	{
		WeaponShoot();
	}
// NUMBERS
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_1) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_1))
	{	// spawn TURRET
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateTurret; // reset timer to frWall
			GameObject* turret = nullptr;
			turret = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Turret"]);
			// set bullet position & rotation as same as 'parent' obj
			((TransformComponent*)turret->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		}
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_2) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_2))
	{	// spawn WALL
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateWall; // reset timer to frWall
			GameObject* wall = nullptr;
			wall = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Wall"]);
			((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
			((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		}
	}
// KEYS
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_Q) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_Q))
	{
		WeaponSwitch();
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_0) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_0))
	{
		GameObject* tempGO = nullptr;
		IdentityComponent* IdCom;
		std::string Id;
		std::unordered_map<size_t, GameObject*> temp = _GlobalContainer._gameObjectFactory->getObjectlist();
		for (auto it : temp)
		{
			IdCom = dynamic_cast<IdentityComponent*>(it.second->GetComponent(ComponentId::IDENTITY_COMPONENT));
			Id = IdCom->ObjectType();
			if ((Id.compare("Enemy") ||
				Id.compare("EnemyTwo") ||
				Id.compare("EnemyThree")
				) && it.second->Get_uID() >= 1000)
			{
				tempGO = it.second;
				tempGO->SetDestory();
			}
		}
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_9) ||
		_GlobalContainer._inputSystem->KeyHold(KeyCode::KEYB_9))
	{
		_god = !_god;
		if (!_god)
			return;
		_health = _healthMax;
		_timerShoot = _timerDeploy = 0.0;
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_P))
	{
		;//_GlobalContainer._sceneManager->ChangeScene(Scenes::WIN);
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_O))
	{
		;//_GlobalContainer._sceneManager->ChangeScene(Scenes::LOSE);
	}
	if (_GlobalContainer._inputSystem->KeyDown(KeyCode::KEYB_I))
	{
		;//_GlobalContainer._sceneManager->ChangeScene(Scenes::MAIN_MENU);
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
	GameObject* bullet = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
	AddForwardForce(bullet->Get_uID(), 70000);
}
void Player::WeaponShoot_Shotgun()
{
	_timerShoot = _firerateShotgun; // cooldown
	Vector3 pos = ((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	float rot = ((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate();
	GameObject* bullet = nullptr;
	// 3 bullets, 1 forward, 2 +- 0.2rad
	bullet = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot);
	AddForwardForce(bullet->Get_uID(), 70000);
	bullet = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot-0.2f);
	AddForwardForce(bullet->Get_uID(), 70000);
	bullet = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(rot+0.2f);
	AddForwardForce(bullet->Get_uID(), 70000);
}
void Player::WeaponShoot_RPG()
{
	--_ammoRpg;
	_timerShoot = _firerateRPG; // cooldown
	GameObject* bullet = _GlobalContainer._gameObjectFactory->CloneGameObject(_GlobalContainer._prefabFactory->GetPrototypeList()["BulletT"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
		((TransformComponent*)(GetSibilingComponent(ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
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
int Player::GetHealthMax()
{
	return _healthMax;
}
int Player::GetProgress()
{
	return _progress;
}
void Player::SetProgress(int val)
{
	_progress = val;
}
int Player::GetProgressMax()
{
	return _progressMax;
}
void Player::ProgressIncement(int in)
{
	_progress += in;
}

void Player::OnTrigger2DEnter(Collider2D* other)
{
	IdentityComponent* idCom = dynamic_cast <IdentityComponent*>(other->GetSibilingComponent(ComponentId::IDENTITY_COMPONENT));
	std::string id = idCom->ObjectType();

	if (id.compare("PickUps_Health"))
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PICK_UPS));

		_health += 2;
		if (_health > 30)
			_health = 30;
		temp->DestoryThis();
	}
	if (id.compare("PickUps_Ammo"))
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PICK_UPS));

		_ammoRpg += 5;
		temp->DestoryThis();
	}
}