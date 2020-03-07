#include "PrecompiledHeaders.h"
#include "HitEffect.h"

void HitEffect::SerialiseComponent(Serialiser& document)
{
}

void HitEffect::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void HitEffect::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void HitEffect::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void HitEffect::Inspect()
{
}

HitEffect::HitEffect() :
	_animation{ nullptr },
	_obj{ nullptr },
	_player{ nullptr }
{
}

HitEffect* HitEffect::Clone()
{
	return new HitEffect(*this);
}

void HitEffect::Init()
{
	_obj = (TransformComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Transform);
	_animation = (AnimationComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Animation);
	_player = (TransformComponent*)MyFactory.GetLinkIDObject(999)->GetComponent(ComponentId::CT_Transform);
	GetParentPtr()->SetEnable(false);
}

void HitEffect::LoadResource()
{

}

void HitEffect::Update(double dt)
{
	if (dt < 0)
		return;

	_obj->SetPos(_player->GetPos());
	_obj->SetRotate(_player->GetRotate());
}

void HitEffect::PlayHit()
{
	GetParentPtr()->SetEnable(true);
	_animation->SetCurrentAnimOnce("Hit");
}
