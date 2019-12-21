#include "LogicComponent.h"
#include "Tools/FileIO/Serialiser.h"

#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

class DataComponent
{
	LogicComponent* parentLogic;
public:
	DataComponent();
	virtual ~DataComponent();

	virtual void SerialiseComponent(Serialiser& document);
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	virtual void Inspect();
};

class DataHealth : public DataComponent
{
public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
};

class DataAmmo : public DataComponent
{

};

class DataAttack : public DataComponent
{

};

class DataPathfinding : public DataComponent
{

};


#endif