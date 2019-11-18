#pragma once
#include "IComponentSystem.h"
#include <string>

#ifndef IDENTITYCOMPONENT_H
#define IDENTITYCOMPONENT_H


//Every Object is compulsory to have this Identity Component to store their uId and Type
class IdentityComponent: public IComponentSystem
{
private:

	unsigned _typeId; // GameObject Type //Change to string
	std::string _ObjectType;
	std::string _name;

public:
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	IdentityComponent(GameObject* parent = nullptr, size_t uId = 0, IComponentSystem * component = nullptr); //Constructor
	IdentityComponent(IdentityComponent* component);

	unsigned GameObjectType() const;

	const std::string& ObjectType() const
	{
		return _ObjectType;
	}

	void SetObjectType(std::string ObjectType)
	{
		_ObjectType = ObjectType;
	}
};


#endif 
