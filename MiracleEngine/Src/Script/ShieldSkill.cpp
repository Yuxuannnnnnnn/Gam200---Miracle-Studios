#include "PrecompiledHeaders.h"
#include "ShieldSkill.h"
#include "Script/HealthController.h"

void ShieldSkill::SerialiseComponent(Serialiser& document)
{
}

void ShieldSkill::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void ShieldSkill::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void ShieldSkill::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void ShieldSkill::Inspect()
{
}

ShieldSkill::ShieldSkill() :
	_timer{ -1.f },
	_animTimer{ -1.f },
	_animation{ nullptr },
	_obj{ nullptr },
	_player{ nullptr },
	_audcom{nullptr}
{
}

ShieldSkill* ShieldSkill::Clone()
{
	return new ShieldSkill(*this);
}

void ShieldSkill::Init()
{
	_obj = GetSibilingComponentObject(Transform);
	_animation = GetSibilingComponentObject(Animation);
	_audcom = GetSibilingComponentObject(Audio);
	_player = GetComponentObject(GetLinkObject(999), Transform);
	GetParentPtr()->SetEnable(false);

	_healthController = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(919),Logic), HealthController);
}

void ShieldSkill::LoadResource()
{

}

void ShieldSkill::Update(double dt)
{
	if (dt < 0)
		return;

	_obj->SetPos(_player->GetPos());
	_obj->SetRotate(_player->GetRotate());

	if (_timer < 0 && _animTimer < 0)
	{
		_animation->SetCurrentAnimOnce("Off");
		_animTimer = (double)_animation->GetMaxFrame() * _animation->GetTimeDelay();
		_audcom->PlaySFX("ShieldBreak");
	}
	else if (_animTimer > 0)
	{
		_animTimer -= dt;

		if (_animTimer < 0)
		{
			((HealthController*)_healthController)->ChargeShield(_cooldownTime);
			GetParentPtr()->SetEnable(false);
		}
	}
	else
		_timer -= dt;
		
}

void ShieldSkill::ActionShield(double skilltimer, double cooldown)
{
	_cooldownTime = cooldown;

	((HealthController*)_healthController)->UseShield(skilltimer);

	GetParentPtr()->SetEnable(true);
	_timer = skilltimer;
	_animTimer = -1.f;
	_animation->SetCurrentAnim("On");
	_animation->SetPlayingOnce(false);
	_audcom->PlaySFX("Activate");
}
