

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
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override { return; }
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
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) override { return; }
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