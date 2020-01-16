

#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

#include "GameObject/Components/Logic/LogicComponent.h"

class DataHealth : public IComponent
{
	LogicComponent* parentLogic;
public:
	DataHealth();
	virtual ~DataHealth();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataHealth* CloneComponent() { return new DataHealth(*this); }
};

class DataAmmo : public IComponent
{
	LogicComponent* parentLogic;
public:
	DataAmmo();
	virtual ~DataAmmo();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataAmmo* CloneComponent() { return new DataAmmo(*this); }
};

//class DataAttack : public DataComponent
//{
//
//};
//
//class DataPathfinding : public DataComponent
//{
//
//};


#endif