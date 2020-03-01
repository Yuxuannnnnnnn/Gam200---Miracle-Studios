#pragma once
#include "../IComponent.h"
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

	int _linkUId;

public:

	virtual void Init() override;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() override;


	const std::string& GetName() const;

	IdentityComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent * component = nullptr); //Constructor
	IdentityComponent(IdentityComponent* component);

	//unsigned GameObjectType() const;


	const std::string& ObjectType() const;

	void SetObjectType(std::string ObjectType);

	int GetLinkID();

	IdentityComponent* CloneComponent() { return new IdentityComponent(*this); }
};


#endif 
