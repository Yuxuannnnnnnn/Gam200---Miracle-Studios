#include "PrecompiledHeaders.h"
#include "ShieldSkill.h"

void ShieldSkill::SerialiseComponent(Serialiser& document)
{
}

void ShieldSkill::DeSerialiseComponent(DeSerialiser& prototypeDoc)
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
	_init{false}
{
}

ShieldSkill* ShieldSkill::Clone()
{
	return new ShieldSkill(*this);
}

void ShieldSkill::Init()
{
	MyLinkFactory.SaveNewLinkID(666, GetParentId());
	_obj = (TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform);
	_animation = (AnimationComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Animation);
	GetParentPtr()->SetEnable(false);
}

void ShieldSkill::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
		return;
		//((AnimationComponent*)this->GetSibilingComponent(ComponentId::CT_Animation))->SetCurrentAnim("Character_BodyFloat_sprite.png");
	}

	if (!_player)
		_player = (TransformComponent*)MyLinkFactory.GetLinkIDObject(999)->GetComponent(ComponentId::CT_Transform);

	_obj->SetPos(_player->GetPos());
	_obj->SetRotate(_player->GetRotate());

	if (_timer < 0 && _animTimer < 0)
	{
		_animation->SetCurrentAnimOnce("Off");
		_animTimer = _animation->GetMaxFrame() * _animation->GetTimeDelay();

		AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
		audcom->PlaySFX("ShieldBreak");
	}
	else if (_animTimer > 0)
	{
		_animTimer -= dt;

		if (_animTimer < 0)
			GetParentPtr()->SetEnable(false);
	}
	else
		_timer -= dt;
		
}

void ShieldSkill::ActionShield(double skilltimer)
{
	GetParentPtr()->SetEnable(true);
	_timer = skilltimer;
	_animation->SetCurrentAnim("On");

	AudioComponent* audcom = (AudioComponent*)(GetSibilingComponent(ComponentId::CT_Audio));
	audcom->PlaySFX("Activate");
}
