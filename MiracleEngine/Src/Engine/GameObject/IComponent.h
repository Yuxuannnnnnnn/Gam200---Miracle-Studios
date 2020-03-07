#pragma once
#include <string>
#include "Tools/FileIO/Serialiser.h"
#include "Tools/FileIO/DeSerialiser.h"
#include "ComponentTypeId.h"

#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H

class GameObject; // forward declaration

class IComponent
{
private:
	GameObject* _ParentPtr;
	size_t _ParentId;
	bool _enable;
public:

	IComponent();
	IComponent(GameObject * parent, size_t uId);	//Initialise Parent Ptr & ParentId
	virtual ~IComponent() = default;	//virtual destructor to delete deerived Components

	virtual void Init() {}
	virtual void LoadResource() {}

//Interface functions to be implemented by Derived Classes
	virtual std::string ComponentName() const = 0; //Every Comoponent has a ComponentName function
	
	//Every Component has to have a serialise function
	virtual void SerialiseComponent(Serialiser& document) = 0;
	virtual void DeSerialiseComponent(DeSerialiser & prototypeDoc) = 0; //Every Component has to have a DeSerialise function
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{

	}
	virtual void Inspect() = 0;	//Every Component has an Inspect function for InspectionImguiWindow
	//virtual IComponent* CloneComponent() = 0;
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{}


	virtual IComponent* CloneComponent() = 0;

	size_t GetParentId() const;
	void SetParentId(size_t inVal);
	GameObject* GetParentPtr();
	void SetParentPtr(GameObject* inVal);

	IComponent* GetSibilingComponent(ComponentId _componentId);

	bool GetEnable() const { return _enable; }
	void SetEnable(bool enable) { _enable = enable; }

	void DestoryThis();
};

#define GetSibilingComponentObject(type) dynamic_cast<type##Component*>(GetSibilingComponent(ComponentId::CT_##type))
#endif
