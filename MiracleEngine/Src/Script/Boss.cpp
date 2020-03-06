#include "PrecompiledHeaders.h"
#include "Script/Boss.h"
#include <cstdlib>
#include <ctime>
#include "EntrancePortal.h"

Boss::Boss() :
	health{ 0 }, healthMax{ 0 }, healthHalf{ 0 }, healthQuart{ 0 },

	idleTimer{ 0.0 }, idleDuration{ 0.0 },

	ammo{ 0 }, ammoMax{ 0 },
	bulletTimer{ 0.0 }, shootROF{ 0.0 }, bulletSpeed{ 0.0 },
	rotationspeed{ 0.0f },

	laserChargeTimer{ 0.0 }, laserChargeDuration{ 0.0 },
	laserFlashTimer{ 0.0 }, laserFlashDuration{ 0.0 },
	laserAliveTimer{ 0.0 }, laserAliveDuration{ 0.0 },

	laserRapidFireNumOfShots{ 0 }, rapidFireShotCount{ 0 },
	laserRapidChargeSpeedUp{ 0.0 },

	_laserChargeStart{ false }, _laserFlashStart{ false }, _laserShootStart{ false },
	_init{ false }, _deathStart{ false },
	_state{ Boss_State::IDLE }, _statePrev{ Boss_State::IDLE },
	playerId{ 0 }, playerPtr{ nullptr }, _dt{ 0.0 }
{
}

Boss::~Boss()
{

}

Boss* Boss::Clone()
{
	return new Boss(*this);
}

void Boss::Init()
{
	// TODO : Add in BulletPrototype for shooting

	for (auto itr : _engineSystems._factory->getObjectlist())
	{
		if ((((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0) &&
			(((LogicComponent*)itr.second->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)))
		{
			playerPtr = itr.second;
			playerId = itr.second->Get_uID();
			break;
		}
	}

	// if got starting anim, follow the DeathAnim style and let it loop within Init() until it is done

	_init = true;
}
void Boss::Update(double dt)
{
	if (_init)
		Init();
	_dt = dt;
	UpdateState();
	RunState();
}

void Boss::UpdateState()
{
	// states should update NOT upwhen when !IDLE_END
	if (_state != Boss_State::IDLE_END)
		return;
	// check death
	if (health < 0 && _state != Boss_State::DEATH)
	{
		_state = Boss_State::DEATH;
		_deathStart = true;
		return;
	}
	// select attack method
	if (health < healthHalf)
	{
		_state = Boss_State::LASER_CHARGE;
	}
	else if (health < healthQuart)
	{
		_state = Boss_State::LASER_CHARGE_RAPID;
	}
	else
	{
		_state = Boss_State::SPIN_SHOOTBULLET;
	}
	return;
}

void Boss::RunState()
{
	switch (_state)
	{
	case Boss_State::IDLE:
		Idle();
		break;
	case Boss_State::DEATH:
		Death();
		break;
	case Boss_State::SPIN_SHOOTBULLET:
		SpinAround();
		ShootBullet();
		break;
	case Boss_State::LASER_CHARGE:
		LookAtPlayer();
		LaserCharge();
		break;
	case Boss_State::LASER_SHOOT:
		LaserShoot();
		break;
	case Boss_State::LASER_CHARGE_RAPID:
		LookAtPlayer();
		LaserCharge(laserRapidChargeSpeedUp);
		break;
	default:
		break;
	}
	if (_state != _statePrev)
	{
		if (DEBUGOUTPUT) std::cout << "DEBUG\t State Change from" << (int)_statePrev << " to " << (int)_state << "\n";
		_statePrev = _state;
	}
}

void Boss::Idle()
{
	idleTimer -= _dt;
	if (idleTimer < 0.0)
	{
		// reset timer
		idleTimer = idleDuration;
		// set to Idle_End
		_state = _statePrev = Boss_State::IDLE_END;
	}
}

void Boss::Death()
{
	if (_deathStart)
	{
		_deathStart = false;
		GetSibilingComponent(ComponentId::CT_CircleCollider2D)->SetEnable(false);
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Death");
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetAnimationPlaying(true);
		return;
	}
	if (((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
	{
		if (((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetCurrentFrame() ==
			(((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame() - 1))
		{
			((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetEnable(false);
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(false);
		}
	}
	// if animation finish playing //if (!((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
	else
	{
		GetParentPtr()->SetDestory();
	}
	return;
}

void Boss::SpinAround()
{
	// rotate = rotatespd * dt
	((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotationA(
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotationA() + (rotationspeed * _dt)
	);
}

void Boss::ShootBullet()
{
	if (ammo)
	{
		bulletTimer -= _dt;
		if (bulletTimer < 0)
		{
			bulletTimer = shootROF;
			GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 50000 * bulletSpeed);
			ammo--;

			//AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
			//audcom->PlaySFX("Shoot");
		}
	}
	else
	{
		ammo = ammoMax;
		_state = Boss_State::IDLE;
	}
}

void Boss::LookAtPlayer()
{
	GameObject* exist = MyFactory.GetObjectWithId(playerId);
	if (exist != nullptr)
	{
		Vector3 dirVec = ((TransformComponent*)exist->GetComponent(ComponentId::CT_Transform))->GetPositionA() -
			((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA();
		Vector3 compareVec = { 0, 1, 0 };
		float dot = dirVec._x * compareVec._x + dirVec._y * compareVec._y;
		float det = dirVec._x * compareVec._y - dirVec._y * compareVec._x;
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate() = -atan2(det, dot);
	}
	else
	{
		std::cout << "WARNING: Player is nullptr.\n";
	}
}

void Boss::LaserCharge(double speedup)
{
	if (_statePrev == Boss_State::IDLE_END)
	{
		_laserChargeStart = true;
	}
	if (_laserChargeStart)
	{
		// play the charge aniamtion
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Charge");
		// set anim speed
		if (speedup != 1.0)
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
			(laserChargeDuration / speedup) / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame());
		_laserChargeStart = false;
	}
	else
		laserChargeTimer -= _dt;
	// on animation end, change state to FiringLaser
	if (!((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
	{
		laserChargeTimer = laserChargeDuration;
		_state = Boss_State::LASER_SHOOT;
	}
}

void Boss::LaserShoot()
{
	// LaserShoot() SHOW FLASH
	if (_statePrev == Boss_State::LASER_CHARGE ||
		_statePrev == Boss_State::LASER_CHARGE_RAPID)
	{
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("Normal");
		_laserShootStart = true;
	}
	if (_laserShootStart)
	{
		_laserShootStart = false;
		// spawn the "flash"
		subObj = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
		((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
	else
		laserFlashTimer -= _dt;
	// LaserShoot() SHOOT LASER
	if (laserFlashTimer < 0)
	{
		_laserShootStart = true;
		subObj->SetDestory(); // delete the "flash"
		laserFlashTimer = laserFlashDuration;
	}
	if (_laserShootStart)
	{
		_laserShootStart = false;
		// spawn the "laser"
		subObj = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
		((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetPos(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
		((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetRotate(
			((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	}
	else
		laserAliveTimer -= _dt;
	// LaserShoot() COMPLETE
	if (laserAliveTimer < 0)
	{
		subObj->SetDestory(); // destroy "laser"
		laserAliveTimer = laserAliveDuration;

		// check if in RAPID_FIRE_MODE and need fire more lasers
		if (health < healthQuart)
		{
			rapidFireShotCount--;
			if (rapidFireShotCount > 0)
				_state = Boss_State::LASER_CHARGE_RAPID;
			else
			{
				rapidFireShotCount = laserRapidFireNumOfShots;
				_state = Boss_State::IDLE;
			}
		}
		else
			_state = Boss_State::IDLE;
	}
}

void Boss::OnCollision2DTrigger(Collider2D* other)
{

}

void Boss::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Health") && document["Health"].IsInt())
	{
		health = healthMax = (document["Health"].GetInt());
		healthHalf = health / 2;
		healthQuart = health / 4;
	}
	if (document.HasMember("IdleDuration") && document["IdleDuration"].IsDouble())
		idleTimer = idleDuration = (document["IdleDuration"].GetDouble());
	if (document.HasMember("AmmoPerSpin") && document["AmmoPerSpin"].IsInt())
		ammo = ammoMax = (document["AmmoPerSpin"].GetInt());
	if (document.HasMember("ShootROF") && document["ShootROF"].IsDouble())
		bulletTimer = shootROF = (document["ShootROF"].GetDouble());
	if (document.HasMember("BulletSpeed") && document["BulletSpeed"].IsDouble())
		bulletSpeed = (document["BulletSpeed"].GetDouble());
	if (document.HasMember("RotationSpeed") && document["RotationSpeed"].IsDouble())
		rotationspeed = (document["RotationSpeed"].GetDouble());
	if (document.HasMember("ChargeDuration") && document["ChargeDuration"].IsDouble())
		laserChargeTimer = laserChargeDuration = (document["ChargeDuration"].GetDouble());
	if (document.HasMember("FlashDuration") && document["FlashDuration"].IsDouble())
		laserFlashTimer = laserFlashDuration = (document["FlashDuration"].GetDouble());
	if (document.HasMember("LaserAliveDuration") && document["LaserAliveDuration"].IsDouble())
		laserAliveTimer = laserAliveDuration = (document["LaserAliveDuration"].GetDouble());
	if (document.HasMember("RapidFireNumOfShots") && document["RapidFireNumOfShots"].IsInt())
		laserRapidFireNumOfShots = rapidFireShotCount = (document["RapidFireNumOfShots"].GetInt());
	if (document.HasMember("RapidFireChargeSpeedUp") && document["RapidFireChargeSpeedUp"].IsDouble())
		laserRapidChargeSpeedUp = (document["RapidFireChargeSpeedUp"].GetDouble());
}

void Boss::DeSerialiseComponent(DeSerialiser& prototypeDoc) {//not being used
}

void Boss::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	//rapidjson::Value value;

	//value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	//prototypeDoc.AddMember("Script2Id", value, allocator);

	//value.SetInt(_health);
	//prototypeDoc.AddMember("Health", value, allocator);

	//value.SetInt(_enemyType);
	//prototypeDoc.AddMember("EnemyType", value, allocator);

	//value.SetDouble(_timerStunCooldown);
	//prototypeDoc.AddMember("StunDuration", value, allocator);

	//value.SetDouble(_moveSpeed);
	//prototypeDoc.AddMember("MoveSpeed", value, allocator);

	//value.SetDouble(_chaseSpeed);
	//prototypeDoc.AddMember("ChaseSpeed", value, allocator);

	//value.SetDouble(_chaseDuration);
	//prototypeDoc.AddMember("ChaseDuration", value, allocator);


	//double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
	//value.SetDouble(attackRangeShoot);
	//prototypeDoc.AddMember("AttackRangeShoot", value, allocator);

	//double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
	//value.SetDouble(attackRangeMelee);
	//prototypeDoc.AddMember("AttackRangeMelee", value, allocator);

}

void Boss::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	//LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	//size_t UId = protoLogicCom->GetScriptContianer()[_type];

	//Enemy* script = (Enemy*)(MyLogicSystem.getScriptPtr(UId));

	//if (!script)
	//{
	//	DeSerialiseComponent(value, allocator);
	//	return;
	//}

	//rapidjson::Value Health;
	//rapidjson::Value EnemyType;
	//rapidjson::Value StunDuration;
	//rapidjson::Value MoveSpeed;
	//rapidjson::Value ChaseSpeed;
	//rapidjson::Value ChaseDuration;
	//rapidjson::Value AttackRangeShoot;
	//rapidjson::Value AttackRangeMelee;

	//bool addComponentIntoSceneFile = false;


	//if (script->_health != _health)
	//{
	//	addComponentIntoSceneFile = true;
	//	Health.SetInt(_health);
	//}

	//if (script->_enemyType != _enemyType)
	//{
	//	addComponentIntoSceneFile = true;
	//	EnemyType.SetInt(_enemyType);
	//}

	//if (script->_timerStunCooldown != _timerStunCooldown)
	//{
	//	addComponentIntoSceneFile = true;
	//	StunDuration.SetDouble(_timerStunCooldown);
	//}

	//if (script->_moveSpeed != _moveSpeed)
	//{
	//	addComponentIntoSceneFile = true;
	//	MoveSpeed.SetDouble(_moveSpeed);
	//}

	//if (script->_chaseSpeed != _chaseSpeed)
	//{
	//	addComponentIntoSceneFile = true;
	//	ChaseSpeed.SetDouble(_chaseSpeed);
	//}

	//if (script->_chaseDuration != _chaseDuration)
	//{
	//	addComponentIntoSceneFile = true;
	//	ChaseDuration.SetDouble(_chaseDuration);
	//}

	//if (script->_attackRangeShoot != _attackRangeShoot)
	//{
	//	addComponentIntoSceneFile = true;

	//	double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
	//	AttackRangeShoot.SetDouble(attackRangeShoot);
	//}

	//if (script->_attackRangeMelee != _attackRangeMelee)
	//{
	//	addComponentIntoSceneFile = true;

	//	double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
	//	AttackRangeMelee.SetDouble(attackRangeMelee);
	//}

	//if (addComponentIntoSceneFile)    //If anyone of component data of obj is different from Prototype
	//{
	//	rapidjson::Value scriptName;

	//	scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
	//	value.AddMember("Script2Id", scriptName, allocator);

	//	if (!Health.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("Health", Health, allocator);
	//	}

	//	if (!EnemyType.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("EnemyType", EnemyType, allocator);
	//	}

	//	if (!StunDuration.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("StunDuration", StunDuration, allocator);
	//	}


	//	if (!MoveSpeed.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("MoveSpeed", MoveSpeed, allocator);
	//	}


	//	if (!ChaseSpeed.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("ChaseSpeed", ChaseSpeed, allocator);
	//	}


	//	if (!ChaseDuration.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("ChaseDuration", ChaseDuration, allocator);
	//	}


	//	if (!AttackRangeShoot.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("AttackRangeShoot", AttackRangeShoot, allocator);
	//	}

	//	if (!AttackRangeMelee.IsNull())    //if rapidjson::value container is not empty
	//	{
	//		value.AddMember("AttackRangeMelee", AttackRangeMelee, allocator);
	//	}
	//}
}

void Boss::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Health ", &health);
	ImGui::Spacing();
	ImGui::InputInt("HealthMax ", &healthMax);
	ImGui::Spacing();
	ImGui::InputDouble("Idle Duration ", &idleDuration);
	ImGui::Spacing();

	ImGui::InputInt("AmmoMax ", &ammoMax);
	ImGui::Spacing();
	ImGui::InputDouble("ShootROF ", &idleDuration);
	ImGui::Spacing();
	ImGui::InputDouble("BulletSpeed ", &idleDuration);
	ImGui::Spacing();
}
