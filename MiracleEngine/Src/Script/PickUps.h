#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef PICKUP_H
#define	PICKUP_H

enum class PickUp_Type
{
	NONE = 0,
	HEALTH_REGEN = 1,
	ROCKET_AMMO = 2,
};

class PickUps : public IScript2
{
private:
	double _lifeTime;
	int _pickupType;
public:
	PickUps();
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	PickUps* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);
};

#endif
