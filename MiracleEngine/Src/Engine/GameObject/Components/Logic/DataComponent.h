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

	IComponent* CloneComponent();
	virtual void CloneComponent(DataComponent* src);
	virtual void BindLuaValues(sol::state& lua, std::string& tableName);
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName);
};
// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
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

	DataMoveComponent* CloneComponent() override;
	virtual void CloneComponent(DataComponent* src) override;
	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override;
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName) override;
};
// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
class DataTransformComponent : public DataComponent
{
	Vector3 _ObjPos, _ObjScale;
	float _ObjRot;
	//Vector3 _SpritePos, _SpriteScale;
	//float _SpriteRot;
public:
	DataTransformComponent();
	virtual ~DataTransformComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataTransformComponent* CloneComponent() override;
	virtual void CloneComponent(DataComponent* src) override;
	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override;
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName) override;
};
// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
class DataPlayerComponent : public DataComponent
{
public:
	float _Health, _HealthMax;
	float _Shield, _ShieldMax, _ShieldRechargeSpeed;
	float _MovementSpeed = 1, _MovementSpeedMax;
public:
	DataPlayerComponent();
	virtual ~DataPlayerComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataPlayerComponent* CloneComponent() override;
	virtual void CloneComponent(DataComponent* src) override;
	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override;
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName) override;
};
// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------
class DataHealthComponent : public DataComponent
{
	float _Health, _HealthMax;
public:
	DataHealthComponent();
	virtual ~DataHealthComponent();
	virtual std::string ComponentName() const override;
	virtual void SerialiseComponent(Serialiser& document) override;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)		override { return; }

	DataHealthComponent* CloneComponent() override;
	virtual void CloneComponent(DataComponent* src) override;
	virtual void BindLuaValues(sol::state& lua, std::string& tableName) override;
	virtual void SaveLuaValues(sol::state& lua, std::string& tableName) override;
};

#endif