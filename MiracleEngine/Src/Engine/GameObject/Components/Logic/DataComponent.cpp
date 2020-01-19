#include "PrecompiledHeaders.h"

DataComponent::DataComponent() {}
DataComponent::~DataComponent() {}
std::string DataComponent::ComponentName() const { return std::string("Data_Health"); }
void DataComponent::SerialiseComponent(Serialiser& document) {}
void DataComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataComponent::Inspect() {}
IComponent* DataComponent::CloneComponent()
	{ std::cout << "WARNING: DataComponent::CloneComponent() being called! \n"; return nullptr; }
void DataComponent::CloneComponent(DataComponent* src)
	{ std::cout << "WARNING: DataComponent::CloneComponent(DataComponent* src) being called! \n"; }
void DataComponent::BindLuaValues(sol::state& lua, std::string& tableName)
	{ std::cout << "WARNING: DataComponent::BindLuaValues() being called! \n"; }
void DataComponent::SaveLuaValues(sol::state& lua, std::string& tableName)
	{ std::cout << "WARNING: DataComponent::SaveLuaValues() being called! \n"; }

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

DataMoveComponent::DataMoveComponent() { if (DEBUG_LUA) std::cout << "DEBUG:\t Ctor: DataMove. \n"; }
DataMoveComponent::~DataMoveComponent() {}
std::string DataMoveComponent::ComponentName() const { return std::string("DataMove"); }
void DataMoveComponent::SerialiseComponent(Serialiser& document) {}
void DataMoveComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataMoveComponent::Inspect() {}
DataMoveComponent* DataMoveComponent::CloneComponent()
	{ return new DataMoveComponent(*this); }
void DataMoveComponent::CloneComponent(DataComponent* src)
{
	DataMoveComponent* comp = reinterpret_cast<DataMoveComponent*>(src);
	_position	= comp->_position;
	_scale		= comp->_scale;
	_rotation	= comp->_rotation;
}
void DataMoveComponent::BindLuaValues(sol::state& lua, std::string& tableName) {
	TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
	_position = temp->GetPos();
	_scale = temp->GetScale();
	_rotation = temp->GetRotate();
	lua[tableName]["POSITION"] = temp->GetPos();
	lua[tableName]["SCALE"] = temp->GetScale();
	lua[tableName]["ROTATION"] = temp->GetRotate();
	DataPlayerComponent* temp1 = (DataPlayerComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_DataPlayer);
	lua[tableName]["SPEED"] = temp1->_MovementSpeed;
}
void DataMoveComponent::SaveLuaValues(sol::state& lua, std::string& tableName) {
	TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
	temp->SetPos(lua[tableName]["POSITION"]);
	temp->SetScale(lua[tableName]["SCALE"]);
	temp->SetRotate(lua[tableName]["ROTATION"]);
}

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

DataTransformComponent::DataTransformComponent() { if (DEBUG_LUA) std::cout << "DEBUG:\t Ctor: DataTransform. \n"; }
DataTransformComponent::~DataTransformComponent() {}
std::string DataTransformComponent::ComponentName() const { return std::string("DataTransform"); }
void DataTransformComponent::SerialiseComponent(Serialiser& document) {}
void DataTransformComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataTransformComponent::Inspect() {}
DataTransformComponent* DataTransformComponent::CloneComponent() {
	return new DataTransformComponent(*this);
}
void DataTransformComponent::CloneComponent(DataComponent* src)
{
	DataTransformComponent* comp = reinterpret_cast<DataTransformComponent*>(src);
	_ObjPos = comp->_ObjPos;
	_ObjScale = comp->_ObjScale;
	_ObjRot = comp->_ObjRot;
}
void DataTransformComponent::BindLuaValues(sol::state& lua, std::string& tableName) {
	TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
	_ObjPos = temp->GetPos();		lua[tableName]["POSITION"] = _ObjPos;
	_ObjScale = temp->GetScale();	lua[tableName]["SCALE"] = _ObjScale;
	_ObjRot = temp->GetRotate();	lua[tableName]["ROTATION"] = _ObjRot;
}
void DataTransformComponent::SaveLuaValues(sol::state& lua, std::string& tableName) {
	TransformComponent* temp = (TransformComponent*)parentLogic->GetSibilingComponent(ComponentId::CT_Transform);
	temp->SetPos(lua[tableName]["POSITION"]);
	temp->SetScale(lua[tableName]["SCALE"]);
	temp->SetRotate(lua[tableName]["ROTATION"]);
}

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

DataPlayerComponent::DataPlayerComponent() { if (DEBUG_LUA) std::cout << "DEBUG:\t Ctor: DataPlayer. \n"; }
DataPlayerComponent::~DataPlayerComponent() {}
std::string DataPlayerComponent::ComponentName() const { return std::string("DataPlayer"); }
void DataPlayerComponent::SerialiseComponent(Serialiser& document) {}
void DataPlayerComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataPlayerComponent::Inspect() {}
DataPlayerComponent* DataPlayerComponent::CloneComponent()
{
	return new DataPlayerComponent(*this);
}
void DataPlayerComponent::CloneComponent(DataComponent* src)
{
	DataPlayerComponent* comp = reinterpret_cast<DataPlayerComponent*>(src);
	_Health					= comp->_Health;
	_HealthMax				= comp->_HealthMax;
	_Shield					= comp->_Shield;
	_ShieldMax				= comp->_ShieldMax;
	_ShieldRechargeSpeed	= comp->_ShieldRechargeSpeed;
	_MovementSpeed			= comp->_MovementSpeed;
}
void DataPlayerComponent::BindLuaValues(sol::state& lua, std::string& tableName)
{
	lua[tableName]["HEALTH"]				= _Health;
	lua[tableName]["HEALTHMAX"]				= _HealthMax;
	lua[tableName]["SHIELD"]				= _Shield;
	lua[tableName]["SHIELDMAX"]				= _ShieldMax;
	lua[tableName]["SHIELDRECHARGESPEED"]	= _ShieldRechargeSpeed;
	lua[tableName]["MOVESPEED"]				= _MovementSpeed;
}
void DataPlayerComponent::SaveLuaValues(sol::state& lua, std::string& tableName)
{
	_Health					= lua[tableName]["HEALTH"];
	_HealthMax				= lua[tableName]["HEALTHMAX"];
	_Shield					= lua[tableName]["SHIELD"];
	_ShieldMax				= lua[tableName]["SHIELDMAX"];
	_ShieldRechargeSpeed	= lua[tableName]["SHIELDRECHARGESPEED"];
	_MovementSpeed			= lua[tableName]["MOVESPEED"];
}

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

DataHealthComponent::DataHealthComponent() { if (DEBUG_LUA) std::cout << "DEBUG:\t Ctor: DataHealth. \n"; }
DataHealthComponent::~DataHealthComponent() {}
std::string DataHealthComponent::ComponentName() const { return std::string("DataHealth"); }
void DataHealthComponent::SerialiseComponent(Serialiser& document) {}
void DataHealthComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataHealthComponent::Inspect() {}
DataHealthComponent* DataHealthComponent::CloneComponent()
{
	return new DataHealthComponent(*this);
}
void DataHealthComponent::CloneComponent(DataComponent* src)
{
	DataHealthComponent* comp = reinterpret_cast<DataHealthComponent*>(src);
	_Health = comp->_Health;
	_HealthMax = comp->_HealthMax;
}
void DataHealthComponent::BindLuaValues(sol::state& lua, std::string& tableName)
{
	lua[tableName]["HEALTH"] = _Health;
	lua[tableName]["HEALTHMAX"] = _HealthMax;
}
void DataHealthComponent::SaveLuaValues(sol::state& lua, std::string& tableName)
{
	_Health = lua[tableName]["HEALTH"];
	_HealthMax = lua[tableName]["HEALTHMAX"];
}