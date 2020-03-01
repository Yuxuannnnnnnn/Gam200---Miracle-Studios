#include "PrecompiledHeaders.h"
#include "RegisterLink.h"

void RegisterLink::SerialiseComponent(Serialiser& document)
{
}

void RegisterLink::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void RegisterLink::Inspect()
{
}

RegisterLink::RegisterLink()
{
}

RegisterLink* RegisterLink::Clone()
{
	return new RegisterLink(*this);
}

void RegisterLink::Init()
{
	MyFactory.SaveNewLinkID(((IdentityComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Identity))->GetLinkID(), GetParentId());
}

void RegisterLink::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
}
