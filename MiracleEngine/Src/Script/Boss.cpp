#include "PrecompiledHeaders.h"
#include "Script/Boss.h"
#include <cstdlib>
#include <ctime>
#include "Script/EntrancePortal.h"
#include "Script/BossHealthController.h"

Boss::Boss() :
	_health{ 0 }, _healthMax{ 0 }, _healthHalf{ 0 }, _healthQuart{ 0 },
	_healthControllerLinkId{ 0 },
	startUpTimer{ 0.0 }, idleTimer{ 0.0 }, idleDuration{ 0.0 },

	ammo{ 0 }, ammoMax{ 0 },
	bulletTimer{ 0.0 }, shootROF{ 0.0 }, bulletSpeed{ 0.0 },
	rotationspeed{ 0.0f },

	laserChargeTimer{ 0.0 }, laserChargeDuration{ 0.0 },
	laserFlashTimer{ 0.0 }, laserFlashDuration{ 0.0 },
	laserAliveTimer{ 0.0 }, laserAliveDuration{ 0.0 },

	laserRapidFireNumOfShots{ 0 }, rapidFireShotCount{ 0 },
	laserRapidChargeSpeedUp{ 0.0 },
	hitTintTimer{ 0.0 }, hitTintDuration{ 0.3 },

	_state{ (int)Boss_State::STARTUP }, _statePrev{ (int)Boss_State::STARTUP }, _stateNext{ (int)Boss_State::STARTUP },
	_laserChargeStart{ false }, _laserFlashStart{ false }, _laserShootStart{ false },
	_init{ false }, _healthHalfStart{ false }, _healthHalfEnd{ false }, _deathStart{ false },
	_transforming{ false }, _redTint{ false }, _justHit{ false },

	playerId{ 0 }, playerPtr{ nullptr }, subObj{ nullptr }, _dt{ 0.0 },
	_HealthController{ nullptr },
	_laserAnimation{ nullptr }
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
	_laserAnimation = GetComponentObject(GetLinkObject(69), Animation);
	_laserGraphic = GetComponentObject(GetLinkObject(69), Graphic);
	_laserGraphic->SetEnable(false);
	_laserCollider = GetComponentObject(GetLinkObject(69), BoxCollider2D);
	_mouthGraphic = GetComponentObject(GetLinkObject(70), Graphic);
	_mouthGraphic->SetEnable(false);

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
	_healthHalf = _healthMax / 2;
	_healthQuart = _healthMax / 4;
	_CurrAnimChain = _StartUp;
	_CurrAnimChainItr = _CurrAnimChain.begin();
	((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("StartUp1");
	AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
	audcom->PlaySFX("StartUp");
	MyAudioSystem.PlayBGM("MusicBGM1", 1.0f); // ask YX where she grab this from

	_HealthController = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(_healthControllerLinkId), Logic), BossHealthController);

	_init = true;
}
void Boss::Update(double dt)
{
	if (!_init)
		Init();
	if (dt < 0)
		return;
	_dt = dt;
	UpdateState();
	RunState();
}

bool Boss::PlayAnimChain(std::vector<std::string> animChain, bool overwrite)
{
	if (overwrite)
	{
		_CurrAnimChain = animChain;
		_CurrAnimChainItr = _CurrAnimChain.begin();
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce(*_CurrAnimChainItr);
		return true;
	}

	if (((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
		return true;
	else {
		if (_CurrAnimChain == animChain) // check it is a new AnimChain
		{
			if (_CurrAnimChainItr == _CurrAnimChain.end()) // if PlayAnimChain need repeat animation
			{
				_CurrAnimChainItr = _CurrAnimChain.begin();
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce(*_CurrAnimChainItr);
				return true;
			}

			if (++_CurrAnimChainItr != _CurrAnimChain.end()) // still got more in the chain
			{
				((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce(*_CurrAnimChainItr);
				return true;
			}
			else // end of chain
				return false;
		}
		else // immediately chaing anim to new anim
		{
			_CurrAnimChain = animChain;
			_CurrAnimChainItr = _CurrAnimChain.begin();
			((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce(*_CurrAnimChainItr);
			return true;
		}
	}
}
bool Boss::PlayOtherAnimChain()
{	
	if (_laserShootStart)
	{
		_laserGraphic->SetEnable(true);
		_CurrOtherAnimChainItr = _Laser.begin();
		_laserAnimation->SetCurrentAnimOnce(*_CurrOtherAnimChainItr);
		return true;
	}

	if (_laserAnimation->IsAnimationPlaying())
		return true;
	else {
		if (*_CurrOtherAnimChainItr == "End")
		{
			_laserGraphic->SetEnable(false);
			_laserCollider->SetEnable(false);
			_laserAnimation->SetAnimationPlaying(false);
			return false;
		}

		if (++_CurrOtherAnimChainItr != _Laser.end()) // still got more in the chain
		{
			_laserAnimation->SetCurrentAnimOnce(*_CurrOtherAnimChainItr);
			if (*_CurrOtherAnimChainItr == "Mid")
				_laserCollider->SetEnable(true);
			else
				_laserCollider->SetEnable(false);
			return true;
		}
		else // end of chain
		{
			_laserGraphic->SetEnable(false);
			_laserCollider->SetEnable(false);
			_laserAnimation->SetAnimationPlaying(false);
			return false;
		}
	}
}
void Boss::UpdateState()
{
	if ((EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_6) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_6)))
		_state = (int)Boss_State::LASER_CHARGE;


	if ((EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_0) ||
		EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_0)))
	{
		((BossHealthController*)_HealthController)->DecreaseHealth(_health);
		_health = -1;
	}

	OnHit();

	// check death
	if (_health < 1 && _state != (int)Boss_State::DEATH)
	{
		_statePrev = _state;
		_state = (int)Boss_State::DEATH;
		_deathStart = true;
		Death();
		return;
	}

	// force skip UpdateState() if Boss currently still in any of these states
	if (_state == (int)Boss_State::STARTUP ||
		_state == (int)Boss_State::IDLE ||
		_state == (int)Boss_State::IDLE_RAGE ||
		_state == (int)Boss_State::TRANSFORMING ||
		_state == (int)Boss_State::DEATH
		) return;

	if (_health <= _healthHalf)
	{
		if (!_healthHalfEnd) // if havent transform
		{
			_state == (int)Boss_State::IDLE_RAGE;
			return;
		}
		_state = (int)Boss_State::SPIN_SHOOTBULLET;
	}
}

void Boss::RunState()
{
	switch (_state)
	{
	case (int)Boss_State::STARTUP:
		StartUp();
		break;
	case (int)Boss_State::TRANSFORMING:
		Transform();
		break;
	case (int)Boss_State::IDLE:
		Idle();
		break;
	case (int)Boss_State::IDLE_RAGE:
		IdleRage();
		break;
	case (int)Boss_State::DEATH:
		Death();
		break;
	case (int)Boss_State::SPIN_SHOOTBULLET:
		SpinShoot();
		break;
	case (int)Boss_State::LASER_CHARGE:
		TrackAndChargeLaser();
		break;
	case (int)Boss_State::LASER_SHOOT:
		LookAtPlayerSlow();
		LaserShoot();
		break;
	default:
		break;
	}
	if (_state != _statePrev)
	{
		if (DEBUGOUTPUT) std::cout << "DEBUG:\t State Change from : " << (int)_statePrev << " to " << (int)_state << "\n";
		_statePrev = _state;
		_dt = 0;

		switch (_state)
		{
		case (int)Boss_State::STARTUP:
			StartUp();
			break;
		case (int)Boss_State::TRANSFORMING:
			Transform();
			break;
		case (int)Boss_State::IDLE:
			Idle();
			break;
		case (int)Boss_State::IDLE_RAGE:
			IdleRage();
			break;
		case (int)Boss_State::DEATH:
			Death();
			break;
		case (int)Boss_State::SPIN_SHOOTBULLET:
			SpinShoot();
			break;
		case (int)Boss_State::LASER_CHARGE:
			TrackAndChargeLaser();
			break;
		case (int)Boss_State::LASER_SHOOT:
			LaserShoot();
			return;
			break;
		default:
			break;
		}
		if (!((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
			TransformNextAnim();
	}
	// by here the next anim needs to be called
}

void Boss::StartUp()
{
	// on anim end, check if got somemore anim to play, else go to next state
	if (!PlayAnimChain(_StartUp))
		_state = (int)Boss_State::IDLE;
}

void Boss::Idle()
{
	if (_health < _healthHalf)
	{
		_state = _stateNext = (int)Boss_State::IDLE_RAGE;
		IdleRage();
		return;
	}
	if (!PlayAnimChain(_Idle))
	{
	//	if (_health < _healthHalf)
	//	{
	//		_state = _stateNext = (int)Boss_State::IDLE_RAGE;
	//	}
	//	else
			_state = (int)Boss_State::LASER_CHARGE;
	}
}
void Boss::IdleRage()
{
	// if havent transform and now need to IDLE_RAGE
	if (!_healthHalfEnd &&
		_stateNext == (int)Boss_State::IDLE_RAGE)
		_healthHalfStart = true;
	if (_healthHalfStart)
	{
		_healthHalfStart = false;
		_healthHalfEnd = true;
		_state = (int)Boss_State::IDLE_END;
		_stateNext = (int)Boss_State::IDLE_RAGE;
		Transform();
		return;
	}

	if (!PlayAnimChain(_IdleRage))
		_state = (int)Boss_State::IDLE_RAGE_END;

	// OLD TIMER METHOD
	//	idleTimer -= _dt;
	//	if (idleTimer < 0.0)
	//	{
	//		idleTimer = idleDuration;
	//		_state = _statePrev = (int)Boss_State::IDLE_RAGE_END;
	//	}
}

void Boss::Death()
{
	if (_deathStart)
	{
		_deathStart = false;

		// set destroy to all enemies
		for (auto& itr : _engineSystems._factory->getObjectlist())
		{
			if (GetComponentObject(itr.second, Identity)->ObjectType().compare("Enemy") == 0 ||
				GetComponentObject(itr.second, Identity)->ObjectType().compare("EnemyTwo") == 0)
				if (!itr.second->GetDestory() && itr.second->GetAlive())
				{
					Enemy* obj = GetScriptByLogicComponent(GetComponentObject(itr.second, Logic), Enemy);

					if (obj)
						obj->SetHealth(-1);
				}
			//((Enemy*)itr.second)->ForceDeath();// ((Enemy*)itr.second)->SetHealth(-1);
		}

		// disable the child displays
		_laserGraphic->SetEnable(false);
		_laserCollider->SetEnable(false);
		_mouthGraphic->SetEnable(false);

		if (_stateNext == (int)Boss_State::SPIN_SHOOTBULLET ||
			_statePrev == (int)Boss_State::SPIN_SHOOTBULLET ||
			_statePrev == (int)Boss_State::SPIN_SHOOTBULLET_END)
		{
			if (DEBUGOUTPUT) std::cout << "DEBUG:\tDeathShooting.\n";
			PlayAnimChain(_DeathShooting, true);
			AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
			audcom->PlaySFX("DeathShoot");
		}
		else // if (_statePrev == (int)Boss_State::IDLE_RAGE || _statePrev == (int)Boss_State::IDLE_RAGE_END)
		{
			if (DEBUGOUTPUT) std::cout << "DEBUG:\tDeathIdle.\n";
			PlayAnimChain(_DeathIdle, true);
			AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
			audcom->PlaySFX("DeathIdleRage");
		}
		return;
	}
	if (!PlayAnimChain(_CurrAnimChain))
	{
		((GraphicComponent*)this->GetSibilingComponent(ComponentId::CT_Graphic))->SetEnable(false);
		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(false);
		std::string temp = "EntrancePortal";
		((EntrancePortal*)MyLogicSystem.GetScriptList()[((LogicComponent*)(MyFactory.GetLinkIDObject(1239)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]])->IncreaseKillCount(999);
		GetParentPtr()->SetDestory();
	}
	// if animation finish playing //if (!((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())

	return;
}

//if (_state == (int)Boss_State::IDLE_RAGE_END &&
//	_stateNext == (int)Boss_State::SPIN_SHOOTBULLET)
//{	// IDLE_RAGE --> SHOOTING
//	PlayAnimChain(_TransformIdleRageToShoot, true);
//	_state = (int)Boss_State::TRANSFORMING;
//}

void Boss::SpinShoot()
{// TODO : Need do _TransformIdleRageToShoot before spin and shoot
	// if havent transform and now need to SPINSHOOT
	if (!_transforming &&
		_statePrev == (int)Boss_State::IDLE_RAGE_END)
	{
		_state = (int)Boss_State::IDLE_RAGE_END;
		_stateNext = (int)Boss_State::SPIN_SHOOTBULLET;
		Transform();
		return;
	}

	if (!PlayAnimChain(_Shooting))
		PlayAnimChain(_Shooting);
	SpinAround();
	ShootBullet();

	// check if all ammo used, then transform back
	if (_state == (int)Boss_State::SPIN_SHOOTBULLET_END)
	{
		_stateNext = (int)Boss_State::IDLE_RAGE;
		Transform();
		return;
	}
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
			GameObject* bullet = nullptr;
			float rot = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate()
				+ MY_PI / 4;
			Vector3 pos = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos();

			bullet = CreateObject("BulletE");
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot += MY_PI / 2);
			AddForwardForce(bullet->Get_uID(), 70000 * bulletSpeed);
			bullet = CreateObject("BulletE");
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot += MY_PI / 2);
			AddForwardForce(bullet->Get_uID(), 70000 * bulletSpeed);
			bullet = CreateObject("BulletE");
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot += MY_PI / 2);
			AddForwardForce(bullet->Get_uID(), 70000 * bulletSpeed);
			bullet = CreateObject("BulletE");
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(pos);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(rot += MY_PI / 2);
			AddForwardForce(bullet->Get_uID(), 70000 * bulletSpeed);

			ammo--;

			AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
			audcom->PlaySFX("BulletShoot");
		}
	}
	else
	{
		ammo = ammoMax;
		_state = (int)Boss_State::SPIN_SHOOTBULLET_END;
	}
}

void Boss::TrackAndChargeLaser()
{
	LookAtPlayer();
	LaserCharge();
}
void Boss::LookAtPlayer()
{
	for (auto itr : _engineSystems._factory->getObjectlist())
	{
		if ((((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0) &&
			(((LogicComponent*)itr.second->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)))
		{
			playerPtr = itr.second;
			playerId = itr.second->Get_uID();

			Vector3 dirVec = ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA() - 
				((TransformComponent*)playerPtr->GetComponent(ComponentId::CT_Transform))->GetPositionA();
			
			// do matrix mult to the 2 vectors above so it matches the bosses new facing direction
			// x' = xcos - ysin || y' = ycos + xsin
			float currAngle = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate();
			//currAngle += 2 * MY_PI;
			Vector3 compareUp(sin(currAngle), -cos(currAngle), 0); // rotated 0,1,0
			Vector3 compareRight(cos(currAngle), sin(currAngle), 0); // rotated 1,0,0
			
	//	Vec3 diff = _pos - _pivotPoint;
	//	float mag = diff.Length();
	//	float deg = atan2(diff._y, diff._x) + temp;
	//	temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;

			float dot = 0, det = 0, newAngle = 0;
			// check if left or right
			dot = dirVec._x * compareRight._x + dirVec._y * compareRight._y;
			bool rotateRight = (dot > 0) ? true : false;
			dot = dirVec._x * compareUp._x + dirVec._y * compareUp._y;
			det = dirVec._x * compareUp._y - dirVec._y * compareUp._x;
			bool infront = (dot > 0) ? true : false;
			
			newAngle = -atan2(det, dot);

			currAngle = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate();
			det = (det >= 0.00000) ? det : -det;
			if (det > 10)
				if (rotateRight)
				{
					currAngle -= ((rotationspeed * _dt) * (det * _dt));
					((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
				}
				else
				{
					currAngle += ((rotationspeed * _dt) * (det * _dt));
					((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
				}

		//	if (newAngle > currAngle && (det > 10 || det < -10))
		//	{
		//		currAngle += (rotationspeed * _dt);
		//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
		//	}
		//	else if (newAngle < currAngle && (det > 10 || det < -10))
		//	{
		//		currAngle -= (rotationspeed * _dt);
		//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
		//	}
		//	else;
			break;
		}
	}
}

void Boss::LaserCharge(double speedup)
{
	// check if this is first LaserCharge()
	if (_statePrev == (int)Boss_State::IDLE_END)
	{
		PlayAnimChain(_LaserCharge);
		// enable to child objects
			// make laser play 'Laser_blast_start_sprite"
	}
	if (!PlayAnimChain(_LaserCharge))
	{
		_statePrev = (int)Boss_State::LASER_CHARGE;
		_state = (int)Boss_State::LASER_SHOOT;
		
		_laserShootStart = true;
	}

	//	if (_statePrev == (int)Boss_State::IDLE_END)
	//	{
	//		_laserChargeStart = true;
	//		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnimOnce("LaserCharge");
	//	}
	//	if (_laserChargeStart)
	//	{
	//		// set anim speed
	//		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
	//			laserChargeDuration / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame());
	//	//	if (speedup != 1.0)
	//	//		((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetTimeDelay(
	//	//		(laserChargeDuration / speedup) / ((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->GetMaxFrame());
	//		_laserChargeStart = false;
	//	}
	//	else
	//		laserChargeTimer -= _dt;
	//	// on animation end, change state to FiringLaser
	//	if (!((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->IsAnimationPlaying())
	//	{
	//		laserChargeTimer = laserChargeDuration;
	//		_state = (int)Boss_State::LASER_SHOOT;
	//	}
}

void Boss::LookAtPlayerSlow()
{
	for (auto itr : _engineSystems._factory->getObjectlist())
	{
		if ((((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player01") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("Player") == 0 ||
			((IdentityComponent*)itr.second->GetComponent(ComponentId::CT_Identity))->ObjectType().compare("player") == 0) &&
			(((LogicComponent*)itr.second->GetComponent(ComponentId::CT_Logic))->GetScript2Id(ScriptType::SCRIPT_Player)))
		{
			playerPtr = itr.second;
			playerId = itr.second->Get_uID();

			Vector3 dirVec = ((TransformComponent*)this->GetSibilingComponent(ComponentId::CT_Transform))->GetPositionA() -
				((TransformComponent*)playerPtr->GetComponent(ComponentId::CT_Transform))->GetPositionA();

			// do matrix mult to the 2 vectors above so it matches the bosses new facing direction
			// x' = xcos - ysin || y' = ycos + xsin
			float currAngle = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate();
			//currAngle += 2 * MY_PI;
			Vector3 compareUp(sin(currAngle), -cos(currAngle), 0); // rotated 0,1,0
			Vector3 compareRight(cos(currAngle), sin(currAngle), 0); // rotated 1,0,0

	//	Vec3 diff = _pos - _pivotPoint;
	//	float mag = diff.Length();
	//	float deg = atan2(diff._y, diff._x) + temp;
	//	temp2 = Vec3{ mag * cos(deg), mag * sin(deg) } -diff;

			float dot = 0, det = 0, newAngle = 0;
			// check if left or right
			dot = dirVec._x * compareRight._x + dirVec._y * compareRight._y;
			bool rotateRight = (dot > 0) ? true : false;
			dot = dirVec._x * compareUp._x + dirVec._y * compareUp._y;
			det = dirVec._x * compareUp._y - dirVec._y * compareUp._x;
			bool infront = (dot > 0) ? true : false;

			newAngle = -atan2(det, dot);

			currAngle = ((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate();
			det = (det >= 0.00000) ? det : -det;
			if (det > 10)
				if (rotateRight)
				{
					currAngle -= (((rotationspeed * _dt) * (det * _dt)) * 0.1);
					((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
				}
				else
				{
					currAngle += (((rotationspeed * _dt) * (det * _dt)) * 0.1);
					((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
				}

			//	if (newAngle > currAngle && (det > 10 || det < -10))
			//	{
			//		currAngle += (rotationspeed * _dt);
			//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
			//	}
			//	else if (newAngle < currAngle && (det > 10 || det < -10))
			//	{
			//		currAngle -= (rotationspeed * _dt);
			//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->SetRotate(currAngle);
			//	}
			//	else;
			break;
		}
	}
}

void Boss::LaserShoot()
{
	if (_laserShootStart)
	{
		if (DEBUGOUTPUT) std::cout << "DEBUG:\t BOSS SHOOT START.\n";
		PlayOtherAnimChain();
		_laserShootStart = false;
		
		// Change spawn bullet to change childlaser to play other anim, also enable the collider for it
	//	subObj = CreateObject("BulletE");
	//	((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetPos(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
	//	((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetRotate(
	//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
	//	AddForwardForce(subObj->Get_uID(), -70000);

		return;
	}

	laserAliveTimer -= _dt;

// REMOVE THIS SECTION, THIS ONLY FOR TESTING OF THE LASER SHOOT TIMER WORKING PROPERLY
//	subObj = CreateObject("BulletE");
//	((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetPos(
//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
//	((TransformComponent*)subObj->GetComponent(ComponentId::CT_Transform))->SetRotate(
//		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
//	AddForwardForce(subObj->Get_uID(), -70000);


	// LaserShoot() COMPLETE // _state=LASER_SHOOT_END cause need TRANSOFRM back to IDLE
	PlayOtherAnimChain();
	if (laserAliveTimer < 0)
	//if (!PlayOtherAnimChain());
	{
		if (DEBUGOUTPUT) std::cout << "DEBUG:\t BOSS SHOOT END.\n";
		// re-enable animation
		//((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetEnable(true);
		laserAliveTimer = laserAliveDuration;
		subObj = nullptr;
		_state = (int)Boss_State::LASER_SHOOT_END;
		_stateNext = (int)Boss_State::IDLE;
		Transform();
	}
}

void Boss::TransformNextAnim()
{
	switch (_stateNext)
	{
	case (int)Boss_State::IDLE:
		PlayAnimChain(_Idle, true);
		break;
	case (int)Boss_State::IDLE_RAGE:
		PlayAnimChain(_IdleRage, true);
		break;
	case (int)Boss_State::LASER_CHARGE:
		PlayAnimChain(_LaserCharge, true);
		break;
	case (int)Boss_State::SPIN_SHOOTBULLET:
		PlayAnimChain(_Shooting, true);
		break;
	}
}

void Boss::OnHit()
{
	if (_health < 0)
	{
		if (_redTint)
			GetSibilingComponentObject(Graphic)->SetTintColor(glm::vec4(0, 0, 0, 0));
		return;
	}

	if (_justHit)
	{
		_justHit = false;
		_health--;
		((BossHealthController*)_HealthController)->DecreaseHealth();

		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("Hit");
		if (_redTint)
			hitTintTimer = hitTintDuration;
		else
		{
			_redTint = true;
			GetSibilingComponentObject(Graphic)->SetTintColor(glm::vec4(0.3, 0, 0, 0)); // set tint red
		}
	}
	if (_redTint)
	{
		hitTintTimer -= _dt;
		if (hitTintTimer > 0)
			return;
		else
		{
			_redTint = false;
			GetSibilingComponentObject(Graphic)->SetTintColor(glm::vec4(0, 0, 0, 0)); // set tint normal
		}
	}
	else
		hitTintTimer = hitTintDuration;
}

void Boss::Transform()
{
	if (_health < 1)
		return;

	if (!PlayAnimChain(_CurrAnimChain))
	{
		_state = _stateNext;
		_statePrev = (int)Boss_State::TRANSFORMING_END;
		_transforming = false;
		//		TransformNextAnim();
		return;
	}

	if (_state == (int)Boss_State::LASER_SHOOT_END &&
		_stateNext == (int)Boss_State::IDLE)
	{	// LASER_SHOOT --> IDLE
		PlayAnimChain(_TransformLaserToIdle, true);
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("Transform");
		_state = (int)Boss_State::TRANSFORMING;
	}
	if (_state == (int)Boss_State::IDLE_END &&
		_stateNext == (int)Boss_State::IDLE_RAGE)
	{	// IDLE --> IDLE RAGE
		PlayAnimChain(_TransformIdleToIdleRage, true);
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("Transform");
		_state = (int)Boss_State::TRANSFORMING;
	}
	if (_state == (int)Boss_State::IDLE_RAGE_END &&
		_stateNext == (int)Boss_State::SPIN_SHOOTBULLET)
	{	// IDLE_RAGE --> SHOOTING
		PlayAnimChain(_TransformIdleRageToShoot, true);
		_state = (int)Boss_State::TRANSFORMING;
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("Transform");
	}
	if (_state == (int)Boss_State::SPIN_SHOOTBULLET_END &&
		_stateNext == (int)Boss_State::IDLE_RAGE)
	{	// SHOOTING  --> IDLE_RAGE
		PlayAnimChain(_TransformShootToIdleRage, true);
		_state = (int)Boss_State::TRANSFORMING;
		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("TransformReverse");
	}

}


void Boss::OnCollision2DTrigger(Collider2D* other)
{
	std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();
	if (otherType.compare("Bullet") == 0 && _state != (int)Boss_State::STARTUP)
	{
		_justHit = true; // used in OnHit()
	}
}

void Boss::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("StartDuration") && document["StartDuration"].IsDouble())
		startUpTimer = (document["StartDuration"].GetDouble());
	if (document.HasMember("Health") && document["Health"].IsInt())
		_health = _healthMax = (document["Health"].GetInt());
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

	if (document.HasMember("HealthControllerLinkId") && document["HealthControllerLinkId"].IsInt())
		_healthControllerLinkId = (document["HealthControllerLinkId"].GetInt());
}

void Boss::DeSerialiseComponent(DeSerialiser& prototypeDoc) {//not being used
}

void Boss::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetDouble(startUpTimer);
	prototypeDoc.AddMember("StartDuration", value, allocator);
	value.SetInt(_healthMax);
	prototypeDoc.AddMember("Health", value, allocator);
	value.SetDouble(idleDuration);
	prototypeDoc.AddMember("IdleDuration", value, allocator);

	value.SetInt(ammoMax);
	prototypeDoc.AddMember("AmmoPerSpin", value, allocator);
	value.SetDouble(shootROF);
	prototypeDoc.AddMember("ShootROF", value, allocator);
	value.SetDouble(bulletSpeed);
	prototypeDoc.AddMember("BulletSpeed", value, allocator);
	value.SetDouble(rotationspeed);
	prototypeDoc.AddMember("RotationSpeed", value, allocator);

	value.SetDouble(laserChargeDuration);
	prototypeDoc.AddMember("ChargeDuration", value, allocator);
	value.SetDouble(laserFlashDuration);
	prototypeDoc.AddMember("FlashDuration", value, allocator);
	value.SetDouble(laserAliveDuration);
	prototypeDoc.AddMember("LaserAliveDuration", value, allocator);

	value.SetInt(rapidFireShotCount);
	prototypeDoc.AddMember("RapidFireNumOfShots", value, allocator);
	value.SetDouble(laserRapidChargeSpeedUp);
	prototypeDoc.AddMember("RapidFireChargeSpeedUp", value, allocator);


	value.SetInt(_healthControllerLinkId);
	prototypeDoc.AddMember("HealthControllerLinkId", value, allocator);


}

void Boss::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	Boss* script = (Boss*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value StartDuration;
	rapidjson::Value Health;
	rapidjson::Value IdleDuration;

	rapidjson::Value AmmoPerSpin;
	rapidjson::Value ShootROF;
	rapidjson::Value BulletSpeed;
	rapidjson::Value RotationSpeed;

	rapidjson::Value ChargeDuration;
	rapidjson::Value FlashDuration;
	rapidjson::Value LaserAliveDuration;
	rapidjson::Value RapidFireNumOfShots;
	rapidjson::Value RapidFireChargeSpeedUp;
	rapidjson::Value HealthControllerLinkId;

	bool addComponentIntoSceneFile = false;

	if (script->startUpTimer != startUpTimer)
	{
		addComponentIntoSceneFile = true;
		StartDuration.SetDouble(startUpTimer);
	}
	if (script->_healthMax != _healthMax)
	{
		addComponentIntoSceneFile = true;
		Health.SetInt(_healthMax);
	}
	if (script->idleTimer != idleTimer)
	{
		addComponentIntoSceneFile = true;
		IdleDuration.SetDouble(idleTimer);
	}

	if (script->ammoMax != ammoMax)
	{
		addComponentIntoSceneFile = true;
		AmmoPerSpin.SetInt(ammoMax);
	}
	if (script->shootROF != shootROF)
	{
		addComponentIntoSceneFile = true;
		ShootROF.SetDouble(shootROF);
	}
	if (script->bulletSpeed != bulletSpeed)
	{
		addComponentIntoSceneFile = true;
		BulletSpeed.SetDouble(bulletSpeed);
	}
	if (script->rotationspeed != rotationspeed)
	{
		addComponentIntoSceneFile = true;
		RotationSpeed.SetDouble(rotationspeed);
	}

	if (script->laserChargeDuration != laserChargeDuration)
	{
		addComponentIntoSceneFile = true;
		ChargeDuration.SetDouble(laserChargeDuration);
	}
	if (script->laserFlashDuration != laserFlashDuration)
	{
		addComponentIntoSceneFile = true;
		FlashDuration.SetDouble(laserFlashDuration);
	}
	if (script->laserAliveDuration != laserAliveDuration)
	{
		addComponentIntoSceneFile = true;
		LaserAliveDuration.SetDouble(laserAliveDuration);
	}
	if (script->laserRapidFireNumOfShots != laserRapidFireNumOfShots)
	{
		addComponentIntoSceneFile = true;
		RapidFireNumOfShots.SetInt(laserRapidFireNumOfShots);
	}
	if (script->laserRapidChargeSpeedUp != laserRapidChargeSpeedUp)
	{
		addComponentIntoSceneFile = true;
		RapidFireChargeSpeedUp.SetDouble(laserRapidChargeSpeedUp);
	}

	if (script->_healthControllerLinkId != _healthControllerLinkId)
	{
		addComponentIntoSceneFile = true;
		HealthControllerLinkId.SetInt(_healthControllerLinkId);
	}

	if (addComponentIntoSceneFile)    //If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);

		if (!StartDuration.IsNull())
			value.AddMember("StartDuration", StartDuration, allocator);
		if (!Health.IsNull())
			value.AddMember("Health", Health, allocator);
		if (!IdleDuration.IsNull())
			value.AddMember("IdleDuration", IdleDuration, allocator);

		if (!AmmoPerSpin.IsNull())
			value.AddMember("AmmoPerSpin", AmmoPerSpin, allocator);
		if (!ShootROF.IsNull())
			value.AddMember("ShootROF", ShootROF, allocator);
		if (!BulletSpeed.IsNull())
			value.AddMember("BulletSpeed", BulletSpeed, allocator);
		if (!RotationSpeed.IsNull())
			value.AddMember("RotationSpeed", RotationSpeed, allocator);

		if (!ChargeDuration.IsNull())
			value.AddMember("ChargeDuration", ChargeDuration, allocator);
		if (!FlashDuration.IsNull())
			value.AddMember("FlashDuration", FlashDuration, allocator);
		if (!LaserAliveDuration.IsNull())
			value.AddMember("LaserAliveDuration", LaserAliveDuration, allocator);
		if (!RapidFireNumOfShots.IsNull())
			value.AddMember("RapidFireNumOfShots", RapidFireNumOfShots, allocator);
		if (!RapidFireChargeSpeedUp.IsNull())
			value.AddMember("RapidFireChargeSpeedUp", RapidFireChargeSpeedUp, allocator);

		if (!HealthControllerLinkId.IsNull())
			value.AddMember("HealthControllerLinkId", HealthControllerLinkId, allocator);
	}
}

void Boss::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Current State ", &_state);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::InputInt("Health ", &_health);
	ImGui::Spacing();
	ImGui::InputInt("HealthMax ", &_healthMax);
	ImGui::Spacing();
	ImGui::InputDouble("Idle Duration ", &idleDuration);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::InputInt("AmmoCurr ", &ammo);
	ImGui::Spacing();
	ImGui::InputInt("AmmoMax ", &ammoMax);
	ImGui::Spacing();
	ImGui::InputDouble("ShootROF ", &shootROF);
	ImGui::Spacing();
	ImGui::InputDouble("BulletSpeed ", &bulletSpeed);
	ImGui::Spacing();
	ImGui::InputFloat("Rotate Speed ", &rotationspeed);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::InputDouble("Charge Duration ", &laserChargeDuration);
	ImGui::Spacing();
	ImGui::InputDouble("Flash Duration ", &laserFlashDuration);
	ImGui::Spacing();
	ImGui::InputDouble("Alive Duration ", &laserAliveDuration);
	ImGui::Spacing();
	ImGui::InputInt("Rapid Total Shots ", &laserRapidFireNumOfShots);
	ImGui::Spacing();
	ImGui::InputInt("Rapid Shot Counter ", &rapidFireShotCount);
	ImGui::Spacing();
	ImGui::InputDouble("Rapid Shot Charge Spd Mult ", &laserRapidChargeSpeedUp);
	ImGui::Spacing();
	ImGui::InputInt("Health Controller Linking Id ", &_healthControllerLinkId);
	ImGui::Spacing();
}