#include "PrecompiledHeaders.h"
#include "Script/Boss.h"
#include <cstdlib>
#include <ctime>
#include "EntrancePortal.h"

Boss::Boss() :
	health{ 0 }, healthMax{ 0 }, healthHalf{ 0 }, healthQuart{ 0 },

	idleTimer{ 0.0 }, idleDuration{ 0.0 },

	ammo{ 0 }, ammoMax{ 0 },
	bulletTimer{ 0.0 }, bulletROF{ 0.0 }, rotationspeed{ 0.0f },

	laserChargeTimer{ 0.0 }, laserChargeDuration{ 0.0 },
	laserFlashTimer{ 0.0 }, laserFlashDuration{ 0.0 },
	laserAliveTimer{ 0.0 }, laserAliveDuration{ 0.0 },

	laserRapidFireAmount{ 0 }, laserRelatedDurationSpeedUp{ 0.0 },

	_init{ false }, _deathStart{ false },
	_state{ Boss_State::IDLE }, _statePrev{ Boss_State::IDLE },
	playerId{ 0 }, playerPtr{ nullptr }, _dt{ 0.0 }
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
	// states that will force skip UpdateState()
	if (_state == Boss_State::DEATH)
		return;
	if (_state == Boss_State::IDLE)
		return;

	// check death
	if (health < 0)
	{
		_state = Boss_State::DEATH;
		_deathStart = true;
		return;
	}

	// select attack method
	if (health < healthHalf)
	{
		HalfAtk();
	}
	else if (health < healthQuart)
	{
		QuartAtk();
	}
	else
	{
		_state = Boss_State::SPIN_SHOOTBULLET;
	}
	return;
}

void Boss::RunState()
{
	if (_state == _statePrev)
		return;
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
	case Boss_State::CHARGING_LASER:
		LookAtPlayer();
		LaserCharge();
		break;
	case Boss_State::FIRING_LASER:
		break;
	case Boss_State::RAPID_CHARGING_LASER:
		break;
	case Boss_State::RAPID_FIRING_LASER:
		break;
	default:
		break;
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
		_state = Boss_State::IDLE_END;
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
		((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotationA() + (rotationspeed*_dt)
	);
}

void Boss::ShootBullet()
{
	if (ammo)
	{
		bulletTimer -= _dt;
		if (bulletTimer <= 0)
		{
			bulletTimer = bulletROF;
			GameObject* bullet = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()["BulletE"]);
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetPos(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetPos());
			((TransformComponent*)bullet->GetComponent(ComponentId::CT_Transform))->SetRotate(
				((TransformComponent*)(GetSibilingComponent(ComponentId::CT_Transform)))->GetRotate());
			AddForwardForce(bullet->Get_uID(), 50000);
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
}

void Boss::LaserCharge()
{

	// once charge fin
	_state = Boss_State::FIRING_LASER;
}

void Boss::LaserShoot()
{

}
