#include "PrecompiledHeaders.h"
#include "HitEffect.h"

void HitEffect::SerialiseComponent(Serialiser& document)
{
}

void HitEffect::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void HitEffect::Inspect()
{
}

HitEffect::HitEffect() :
	_animation{ nullptr },
	_obj{ nullptr },
	_player{ nullptr },
	_init{false}
{
}

HitEffect* HitEffect::Clone()
{
	return new HitEffect(*this);
}

void HitEffect::Init()
{
	MyLinkFactory.SaveNewLinkID(667, GetParentId());
	_obj = (TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform);
	_animation = (AnimationComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Animation);
	GetParentPtr()->SetEnable(false);
	_init = true;
}

void HitEffect::Update(double dt)
{
	if (dt < 0)
		return;

	if (!_init)
	{
		Init();
		_init = true;
	}

	if (!_player)
		_player = (TransformComponent*)MyLinkFactory.GetLinkIDObject(999)->GetComponent(ComponentId::CT_Transform);

	_obj->SetPos(_player->GetPos());
	_obj->SetRotate(_player->GetRotate());
}

void HitEffect::PlayHit()
{
	GetParentPtr()->SetEnable(true);
	_animation->SetCurrentAnimOnce("Hit");
}
