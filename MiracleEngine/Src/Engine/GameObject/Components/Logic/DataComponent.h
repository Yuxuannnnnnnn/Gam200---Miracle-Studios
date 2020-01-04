

#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

#include "GameObject/Components/Logic/LogicComponent.h"

class DataComponent : public IComponent
{
	LogicComponent* parentLogic;
public:
	DataComponent();
	virtual ~DataComponent();

	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { return; }

};

class DataHealth : public DataComponent
{
public:
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
};

class DataAmmo : public DataComponent
{
public:
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
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