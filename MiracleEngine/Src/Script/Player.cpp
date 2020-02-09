#include "PrecompiledHeaders.h"
#include "Player.h"
#include "ShieldSkill.h"
#include "HealthController.h"

void Player::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ShieldDuration") && document["ShieldDuration"].IsDouble())
		_timerShield = _timerShieldDuration = document["ShieldDuration"].GetDouble();
	
	if (document.HasMember("ShieldCooldown") && document["ShieldCooldown"].IsDouble())
		_timerShieldCooldown = document["ShieldCooldown"].GetDouble();

	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = _healthMax = document["Health"].GetInt();

	if (document.HasMember("WeaponActive") && document["WeaponActive"].IsInt())
		_weaponActive = document["WeaponActive"].GetInt();

	if (document.HasMember("AmmoRpg") && document["AmmoRpg"].IsInt())
		_ammoRpg = document["AmmoRpg"].GetInt();

	if (document.HasMember("AmmoTurret") && document["AmmoTurret"].IsInt())
		_ammoTurret = document["AmmoTurret"].GetInt();

	if (document.HasMember("AmmoWall") && document["AmmoWall"].IsInt())
		_ammoWall = document["AmmoWall"].GetInt();

	if (document.HasMember("FireratePistol") && document["FireratePistol"].IsDouble())
		_fireratePistol = document["FireratePistol"].GetDouble();

	if (document.HasMember("FirerateShotgun") && document["FirerateShotgun"].IsDouble())
		_firerateShotgun = document["FirerateShotgun"].GetDouble();

	if (document.HasMember("FirerateRpg") && document["FirerateRpg"].IsDouble())
		_firerateRPG = document["FirerateRpg"].GetDouble();

	if (document.HasMember("FirerateTurret") && document["FirerateTurret"].IsDouble())
		_firerateTurret = document["FirerateTurret"].GetDouble();

	if (document.HasMember("FirerateWall") && document["FirerateWall"].IsDouble())
		_firerateWall = document["FirerateWall"].GetDouble();
}

void Player::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
//	rapidjson::Value value;
//// Logic Data - General
//	value.SetDouble(_timerShieldDuration);
//	prototypeDoc.AddMember("ShieldDuration", value);
//	value.Clear();
//	value.SetDouble(_timerShieldCooldown);
//	prototypeDoc.AddMember("ShieldCooldown", value);
//	value.Clear();
//	value.SetInt(_health);
//	prototypeDoc.AddMember("Health", value);
//	value.Clear();
//	value.SetInt(_weaponActive);
//	prototypeDoc.AddMember("WeaponActive", value);
//	value.Clear();
//// Logic Data - Weapons
//	value.SetInt(_ammoRpg);
//	prototypeDoc.AddMember("AmmoRpg", value);
//	value.Clear();
//	value.SetInt(_ammoTurret);
//	prototypeDoc.AddMember("AmmoTurret", value);
//	value.Clear();
//	value.SetInt(_ammoWall);
//	prototypeDoc.AddMember("AmmoWall", value);
//	value.Clear();
//	value.SetDouble(_fireratePistol);
//	prototypeDoc.AddMember("FireratePistol", value);
//	value.Clear();
//	value.SetDouble(_firerateShotgun);
//	prototypeDoc.AddMember("FirerateShotgun", value);
//	value.Clear();
//	value.SetDouble(_firerateRPG);
//	prototypeDoc.AddMember("FirerateRpg", value);
//	value.Clear();
//	value.SetDouble(_firerateTurret);
//	prototypeDoc.AddMember("FirerateTurret", value);
//	value.Clear();
//	value.SetDouble(_firerateWall);
//	prototypeDoc.AddMember("FirerateWall", value);
//	value.Clear();
}

void Player::Inspect()
{
// Logic Data - General
	ImGui::Spacing();
	ImGui::InputDouble("ShieldDuration ", &_timerShieldDuration);
	ImGui::Spacing();
	ImGui::InputDouble("ShieldCooldown ", &_timerShieldCooldown);
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
	_timerShield{ 0 }, _timerShieldDuration{ 0 },
	_health{ 30 }, _healthMax{ 30 },
	_progress{ 0 }, _progressMax{ 30 },
	_progressLevel{ 0 },

	_timerGodSwitch{ 0 }, _timerGodSwitchDelay{ 0.5 },
	_shieldOn{ false },
	_timerSwitch{ 0 }, _timerSwitchDelay{ 0.5 },
	_timerShieldActivateCooldown{ 0 }, _timerShieldCooldown{ 1.5 },
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

	_timerProg{ 0.0 }, _timerProgCooldown{ 1.0 },

	_moving{ false },
	_animState{ 0 }, _animStatePrev{ 0 },
	_muzzleTransfrom{ nullptr },
	_muzzleAnimation{ nullptr },
	_animTime{ -1.0 },
	_objTransfrom{ nullptr },
	_healthBar{ nullptr }
{
}

Player* Player::Clone()
{
	return new Player(*this);
}

void Player::Init()
{
	for (auto& it : GetParentPtr()->GetChildList())
	{
		_muzzleTransfrom = (TransformComponent*)it.second->GetComponent(ComponentId::CT_Transform);
		_muzzleAnimation = (AnimationComponent*)it.second->GetComponent(ComponentId::CT_Animation);
		break;
	}

	MyLinkFactory.SaveNewLinkID(999, GetParentId());
	_objTransfrom = (TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform);

	if(_muzzleAnimation)
		_muzzleAnimation->SetAnimationPlaying(false);

	// find Camera
	//std::unordered_map<size_t, GameObject*> temp = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();

	for (auto& idPair : GetComponentMap(Identity))
	{
		if (((IdentityComponent*)idPair.second)->ObjectType().compare("Camera"))
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
		return;
		//((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Character_BodyFloat_sprite.png");
	}

	if (_animTime > 0)
	{
		_animTime -= dt;

		if (_animTime <= 0)
			_muzzleAnimation->SetAnimationPlaying(false);
	}


	if (_god)
	{
		_health = _healthMax;
		_ammoRpg = _ammoTurret = _ammoWall = 10;
		_timerShoot = _timerDeploy = 0.0;
	}
	if (_health == 0)
	{
		_animState = 0;
		// trigger game end state/thing
	}

	_timerShoot -= dt;
	_timerDeploy -= dt;
	_timerProg -= dt;
	_timerSwitch -= dt;
	_timerGodSwitch -= dt;

	UpdateInput();
	UpdateCamera();
	UpdateUI();
	UpdateShield(dt);

// anim updating related logic
	_animState = _moving ? 1 : 2;
	//_animState = _shieldOn ? 4 : 3;
// setting animation state
	if (_animState != _animStatePrev)
	{
		_animStatePrev = _animState;
		if (_animState == 0) // die
		{
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Death");
			_timerDeath = (((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetTimeDelay()
				* (float)((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame());
		}
		if (_animState == 1) // start moving
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Move");
		//if (_animState == 2) // stopped moving
		//	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Attack");

		//// ANIM NOTE: Shields are to be a seperate entitiy to the actual player
		//// so only the logic to set the anim of that obj is here
		//if (_animState == 3) // shield off
		//	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("ShieldBreak");
		//if (_animState == 4) // shield on
		//	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("ShieldIdle");
	}
	else
		_animStatePrev = _animState;
}

void Player::UpdateCamera()
{
	//auto a = EngineSystems::GetInstance()._graphicsSystem;
	/*a->GetCamera().SetCameraPos(((TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform))->GetPos()._x,
		((TransformComponent*)GetSibilingComponent(ComponentId::CT_Transform))->GetPos()._y);*/
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
		_progressLevel++;
	}
	// set percents
	//EngineSystems::GetInstance()._graphicsSystem->SetHealthPercentage(static_cast<float>(_health) / _healthMax);
	//EngineSystems::GetInstance()._graphicsSystem->SetProgressPercentage(static_cast<float>(_progress) / _progressMax);
}

void Player::UpdateInput()
{
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_O))
		DamagePlayer(1);

 //OTHERS
	//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
	//	_InputStyle = INGAME_PAUSE_ESCAPE;

// SCALE
	//Vector3 scaleVec = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetScale();
	//if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
	//	scaleVec._x -= 1;
	//if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
	//	scaleVec._x += 1;
	//if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_UP))
	//	scaleVec._y += 1;
	//if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
	//	scaleVec._y -= 1;
	//((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetScale(scaleVec);

// MOVEMENT
	_moving = false;
	float spd = 3.f * 10000; // get spd
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_W))
	{

		MyAudioSystem.PlayBGM("Level1", 1.0f);

		_moving = true;
		AddForce(GetParentId(), Vector3(0, 1, 0), spd);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
	{
		_moving = true;
		AddForce(GetParentId(), Vector3(-1, 0, 0), spd);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
	{
		_moving = true;
		AddForce(GetParentId(), Vector3(1, 0, 0), spd);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
	{
		_moving = true;
		AddForce(GetParentId(), Vector3(0, -1, 0), spd);
	}

// MOUSE
	Vector3 aimVector = GetMousePos(); // use aimVector to determine direction player is facing
	aimVector.SetZ(0.f);
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(-atan2(det, dot));
	//((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(atan(aimVector._y / aimVector._x));

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::MOUSE_LBUTTON))
	{
		WeaponShoot();
		
		
		/*GameObject* turret = nullptr;
		turret = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Turret"]);
		((TransformComponent*)turret->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());

		AnimationComponent* anim = (AnimationComponent *)turret->GetComponent(ComponentId::CT_Animation);
		anim->SetPlayingOnce(true);

		GraphicComponent* graphic = (GraphicComponent*)turret->GetComponent(ComponentId::CT_Graphic);
		graphic->SetAlpha(0.6f);*/




		// wait for audio system deserialize

		/*AudioComponent* audioptr = (AudioComponent*)this->GetSibilingComponent(ComponentId::CT_Audio);
		if (audioptr)
		{
			audioptr->PlaySFX("Button");
		}*/

		//MyAudioSystem.PlayBGM("Level1.ogg", 0.5f);

		//MyAudioSystem.PlaySFX("Coin.ogg");

		// ANIM: play firing animation here
		// ANIM NOTE: Shields are to be a seperate entitiy to the actual player
		// so only the logic to set the anim of that obj is here
		


	}
	//Right click to activate shield, play shield animation.
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_RBUTTON) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::MOUSE_RBUTTON))
	{
		// check if can actiavate shield
		if (_timerShieldActivateCooldown <= 0)
		{
			if (!_shieldSkill)
			{
				std::string temp = "ShieldSkill";
				_shieldSkill = MyLogicSystem.GetScriptList()[((LogicComponent*)(MyLinkFactory.GetLinkIDObject(666)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]];
			}


			_shieldOn = true;
			((ShieldSkill*)_shieldSkill)->ActionShield(_timerShieldDuration);
			_timerShieldActivateCooldown = _timerShieldDuration + _timerShieldCooldown;
		}
	
	}

// NUMBERS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_1))
	{	// spawn TURRET
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateTurret; // reset timer to frWall
			GameObject* turret = nullptr;
			turret = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Turret"]);
			// set bullet position & rotation as same as 'parent' obj
			((TransformComponent*)turret->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos() + aimVector.Normalized() * 100.f);
		}
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_2) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_2))
	{	// spawn WALL
		if (_timerDeploy <= 0)
		{
			_timerDeploy = _firerateWall; // reset timer to frWall
			GameObject* wall = nullptr;
			wall = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Wall"]);
			((TransformComponent*)wall->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)wall->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
		}
	}
// KEYS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_Q) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Q))
	{
		if (_timerSwitch < 0)
			WeaponSwitch();
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_0) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_0))
	{
		GameObject* tempGO = nullptr;
		IdentityComponent* IdCom;
		std::string Id;
		std::unordered_map<size_t, GameObject*> temp = MyFactory.getObjectlist();
		for (auto it : temp)
		{
			IdCom = dynamic_cast<IdentityComponent*>(it.second->GetComponent(ComponentId::CT_Identity));
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

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_9) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_9))
	{
		if (_timerGodSwitch < 0)
		{
			_god = !_god;
			_timerGodSwitch = _timerGodSwitchDelay;
		}
		if (_god)
		{
			_health = _healthMax;
			_timerShoot = _timerDeploy = 0.0;
		}
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_P))
	{
		;//EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::WIN);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_O))
	{
		;//EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::LOSE);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_I))
	{
		;//EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::MAIN_MENU);
	}
}

void Player::UpdateShield(double dt)
{
	//if (_shieldOn)
	//{
	//	_timerShield -= dt;

	//	// check if need turn shieldOff
	//	if (_timerShield < 0.0)
	//	{
	//		// start the cooldown
	//		_timerShieldActivateCooldown = _timerShieldCooldown;
	//		// reset the shieldOn duration
	//		_timerShield = _timerShieldCooldown;
	//		_shieldOn = false;
	//	}
	//}
	//else //_shieldOff
	//{
	//{
		// cooldown countdown
		_timerShieldActivateCooldown -= dt;
	
}

void Player::WeaponSwitch()
{
	// reset switch delay timer
	_timerSwitch = _timerSwitchDelay;
	// loop available weapons 1,2,3,1,2,3...
	(_weaponActive != 3) ? ++_weaponActive : _weaponActive = 1;
	// reset timer so can shoot immediately
	_timerShoot = 0;
}

void Player::WeaponShoot()
{


	// 'snap' weapon selection to lowest or highest value
	_weaponActive < 1 ? _weaponActive = 1 : _weaponActive;
	_weaponActive > 3 ? _weaponActive = 3 : _weaponActive;
	if (_timerShoot <= 0)
	{
		if(!_muzzleAnimation->GetEnable())
			_muzzleAnimation->SetEnable(true);

		_muzzleAnimation->SetCurrentAnimOnce("Shoot");
		_animTime = _muzzleAnimation->GetMaxFrame() * _muzzleAnimation->GetTimeDelay();

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
			if (_ammoRpg)
				WeaponShoot_RPG();
			break;
		}
		default:
			break;
		}
	}
}

void Player::WeaponShoot_Pistol()
{
	_timerShoot = _fireratePistol; // cooldown
	GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	AddForwardForce(bullet->Get_uID(), 70000.0 * 2.f);

	AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
	audcom->PlaySFX("Shoot");
}
void Player::WeaponShoot_Shotgun()
{
	_timerShoot = _firerateShotgun; // cooldown
	Vector3 pos = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos();
	float rot = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate();
	GameObject* bullet = nullptr;
	// 3 bullets, 1 forward, 2 +- 0.2rad
	bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot);
	AddForwardForce(bullet->Get_uID(), 70000 * 1.5f);
	bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot-0.2f);
	AddForwardForce(bullet->Get_uID(), 70000 * 1.5f);
	bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["Bullet"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot+0.2f);
	AddForwardForce(bullet->Get_uID(), 70000 * 1.5f);

	AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
	audcom->PlaySFX("Shoot");
}
void Player::WeaponShoot_RPG()
{
	--_ammoRpg;
	_timerShoot = _firerateRPG; // cooldown
	GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletT"]);
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	AddForwardForce(bullet->Get_uID(), 70000);

	AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
	audcom->PlaySFX("Shoot");
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

int Player::GetProgressLevel() const
{
	return _progressLevel;
}

void Player::DamagePlayer(int dmg)
{
	if (_god)
		return;
	else
	{
		if (!_healthBar)
		{
			std::string temp = "HealthController";
			_healthBar = MyLogicSystem.GetScriptList()[((LogicComponent*)(MyLinkFactory.GetLinkIDObject(919)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]];
		}
		
		((HealthController*)_healthBar)->DecreaseHealth(dmg);
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("GetHit");

		_health -= dmg;
	}
}

void Player::OnCollision2DTrigger(Collider2D* other)
{
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();
	if (!otherType.compare("BulletE"))
	{
		DamagePlayer();
	}
	if (!otherType.compare("Enemy"))
	{
		DamagePlayer(2);
	}
}

void Player::OnTrigger2DEnter(Collider2D* other)
{
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();

	if (!otherType.compare("PickUps_Health"))
	{
		other->GetParentPtr()->SetDestory();

		if (_god)
			return;

		if (!_healthBar)
		{
			std::string temp = "HealthController";
			_healthBar = MyLogicSystem.GetScriptList()[((LogicComponent*)(MyLinkFactory.GetLinkIDObject(919)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]];
		}
		((HealthController*)_healthBar)->IncreaseHealth(2);
		_health += 2;
		
		if (_health > _healthMax)
			_health = _healthMax;
		
	}
	if (!otherType.compare("PickUps_Ammo"))
	{
		_ammoRpg += 5;
		other->GetParentPtr()->SetDestory();
	}



	/*IdentityComponent* idCom = dynamic_cast <IdentityComponent*>(other->GetSibilingComponent(ComponentId::CT_Identity));
	std::string id = idCom->ObjectType();

	if (id.compare("PickUps_Health"))
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::CT_Logic, ScriptId::PICK_UPS));

		_health += 2;
		if (_health > 30)
			_health = 30;
		temp->DestoryThis();
	}
	if (id.compare("PickUps_Ammo"))
	{
		PickUps* temp = (PickUps*)(other->GetParentPtr()->GetComponent(ComponentId::CT_Logic, ScriptId::PICK_UPS));

		_ammoRpg += 5;
		temp->DestoryThis();
	}*/
}
