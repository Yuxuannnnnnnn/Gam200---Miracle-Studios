#include "PrecompiledHeaders.h"
#include "Script/Boss.h"
#include <cstdlib>
#include <ctime>
#include "EntrancePortal.h"

Boss::Boss() :
	health{ 0 }, healthMax{ 0 }, healthHalf{ 0 }, healthQuart{ 0 },

	idleTimer{ 0.0 }, idleDuration{ 0.0 },
	bulletFireAmount{ 0 }, bulletFireAmountMax{ 0 }, bulletROF{ 0.0 }, rotationspeed{ 0.0f },

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
	// find player
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
		return;
	}
	// determine which state Boss is in
	if (health < healthHalf)
		HalfAtk();
	else if (health < healthQuart)
		QuartAtk();
	else
	{
		// default shooting
		// spin and shoot
	}
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
	case Boss_State::CHARGING_LASER:
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
	
}

void Boss::SpinAround()
{
	// rotate = rotatespd * dt
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