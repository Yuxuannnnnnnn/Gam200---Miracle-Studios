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
	std::string _name;

public:
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	IdentityComponent(GameObject* parent, size_t uId, IComponentSystem * component = nullptr); //Constructor

	unsigned GameObjectType() const;
};


#endif 
