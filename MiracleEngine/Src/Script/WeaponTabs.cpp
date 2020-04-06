#include "PrecompiledHeaders.h"
#include "WeaponTabs.h"

void WeaponTabs::SerialiseComponent(Serialiser& document)
{
}

void WeaponTabs::Inspect()
{
}

WeaponTabs::WeaponTabs()
{
}

WeaponTabs* WeaponTabs::Clone()
{
	return new WeaponTabs(*this);
}

void WeaponTabs::Init()
{
	_bulletPos = GetComponentObject(GetLinkObject(401), Transform)->GetPositionA()._y;
	_3bulletPos = GetComponentObject(GetLinkObject(402), Transform)->GetPositionA()._y;

	_shieldGlow = GetLinkObject(403);
	_shieldGlow->SetEnable(false);

	_selectorRight = GetComponentObject(GetLinkObject(404), Transform);
	_selectorLight = GetComponentObject(GetLinkObject(405), Transform);
}

void WeaponTabs::LoadResource()
{
}

void WeaponTabs::Update(double dt)
{
}

void WeaponTabs::SelectWeapon(int weapon)
{

	float newY;

	if (weapon == 1)
		newY = _bulletPos;
	else if (weapon == 2)
		newY = _3bulletPos;
	else
		return;


	_selectorRight->SetPos({ _selectorRight->GetPositionA()._x, newY, 1.0f });
	_selectorLight->SetPos({ _selectorLight->GetPositionA()._x, newY, 1.0f });

}

void WeaponTabs::EnableShield(bool enable)
{
	_shieldGlow->SetEnable(enable);
}
