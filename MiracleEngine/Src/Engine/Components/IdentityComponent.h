#pragma once
#include "Interfaces/IComponent.h"
#include <string>

#ifndef IDENTITYCOMPONENT_H
#define IDENTITYCOMPONENT_H


//Every Object is compulsory to have this Identity Component to store their uId and Type
class IdentityComponent: public IComponent
{
private:

	//unsigned _typeId;  //Change to string
	std::string _ObjectType; // GameObject Type
	std::string _name;

private:
//Level Editor
    char _current_ObjectType[100];
	char _current_Name[100];


public:
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
	void SaveComponent() override
	{
		_ObjectType = _current_ObjectType; //save gameObjectType
		_name = _current_Name;
	}



	IdentityComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent * component = nullptr); //Constructor
	IdentityComponent(IdentityComponent* component);

	//unsigned GameObjectType() const;

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
