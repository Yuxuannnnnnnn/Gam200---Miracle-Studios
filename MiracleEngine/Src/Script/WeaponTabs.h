#pragma once
#include "GameObject/Components/Logic/IScript2.h"


class WeaponTabs : public IScript2
{
private:
	float _bulletPos;
	float _3bulletPos;

	GameObject* _shieldGlow;

	TransformComponent* _selectorRight;
	TransformComponent* _selectorLight;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) {};

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) {};

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) {};

	void Inspect();

	WeaponTabs();
	WeaponTabs* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void SelectWeapon(int weapon);

	void EnableShield(bool enable);
};

