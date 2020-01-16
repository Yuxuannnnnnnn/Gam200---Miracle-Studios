#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <sol/assert.hpp> // note need to remove this, i dont think this is allowed for public use
#include <lua/lua.h>

#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

#include "GameObject/Components/Logic/LogicComponent.h"

class DataComponent : public IComponent {
public:
	LogicComponent* parentLogic;

	DataComponent();
	virtual ~DataComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) override { return; }

	IComponent* CloneComponent()
		{ std::cout << "WARNING: DataComponent::CloneComponent() being called! \n"; return nullptr; }

	virtual void BindLuaValues(sol::state& lua, std::string& tableName)
		{ std::cout << "WARNING: DataComponent::BindLuaValues() being called! \n"; }
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName)
		{ std::cout << "WARNING: DataComponent::SaveLuaValues() being called! \n"; }
};

//		changed class DataHealth : public IComponent
//		to class DataHealth : public DataComponent
//		same as below
//		use the comment below on the "ShyYu RegisterComponentThing" on Desktop to set up the RegisterComponent
//			do this after shyyu push
		// BRANDON ADD THIS SHIT


class DataMoveComponent : public DataComponent
{
	Vector3 _position, _scale;
	float _rotation;
public:
	DataMoveComponent();
	virtual ~DataMoveComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataMoveComponent* CloneComponent() { return nullptr; }

	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override {
		TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
		_position = temp->GetPos();
		_scale = temp->GetScale();
		_rotation = temp->GetRotate();
		lua[tableName]["POSITION"] = &_position;
		lua[tableName]["SCALE"] = &_scale;
		lua[tableName]["ROTATION"] = &_rotation;
	}
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName) override {
		TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
		temp->SetPos(lua[tableName]["POSITION"]);
		temp->SetScale(lua[tableName]["SCALE"]);
		temp->SetRotate(lua[tableName]["ROTATION"]);
	}
};

class DataHealth : public DataComponent
{
	int _Health;
public:
	DataHealth();
	virtual ~DataHealth();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override {
		 lua[tableName]["HEALTH"] = &_Health;
	}
	DataHealth* CloneComponent() { return new DataHealth(*this); }
};

class DataShieldComponent : public DataComponent
{
	double _Capacity;
public:
	DataShieldComponent();
	virtual ~DataShieldComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override {
		lua[tableName]["DATA"] = _Capacity;
	}
	DataShieldComponent* CloneComponent() { return new DataShieldComponent(*this); }
};

//class DataAmmo : public DataComponent
//{
//	LogicComponent* parentLogic;
//
//public:
//	DataAmmo();
//	virtual ~DataAmmo();
//	virtual std::string ComponentName() const override;
//	virtual void SerialiseComponent(Serialiser& document) override;
//	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
//	virtual void Inspect() override;
//	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }
//
//	DataAmmo* CloneComponent() { return nullptr; }
//
//	virtual void BindLuaValues(sol::state& lua) {
//		lua["DATA"] = srcDataList["data"];
//	}
//	void Update(double dt)
//	{
//	}
//};

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