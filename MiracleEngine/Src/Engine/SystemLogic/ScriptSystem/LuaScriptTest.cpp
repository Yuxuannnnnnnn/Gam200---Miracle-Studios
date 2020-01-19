#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"

Script_Move::Script_Move()
{
	_Name = "ScriptMove";
	_DataDep = { ToString(ComponentId::CT_DataMove) };
}
void Script_Move::Bind(sol::state& lua, GameObject* src)
{
	// check if src != nullptr
	if (!src) {
		if (DEBUG_LUA)
			std::cout << "WARNING: " << _Name << "has no GO* src.\n";
		return;
	}
	// check if all DataDependencies are there
	for (auto itr : _DataDep) {
		if (!src->GetComponent(ToComponentID(itr)))
		{
			if (DEBUG_LUA)
				std::cout << "WARNING: " << _Name << "has no GO* src.\n";
			return;
		}
	}
	// bind related values
	TransformComponent* temp = (TransformComponent*)src->GetComponent(ComponentId::CT_Transform);
	lua["ScriptMove"]["POSITION"] = temp->GetPos();
	lua["ScriptMove"]["SCALE"] = temp->GetScale();
	lua["ScriptMove"]["ROTATION"] = temp->GetRotate();
	DataPlayerComponent* temp1 = (DataPlayerComponent*)src->GetComponent(ComponentId::CT_DataPlayer);
	lua["ScriptMove"]["SPEED"] = &temp1->_MovementSpeed;
	if (DEBUG_LUA)
	{
		if (!lua["ScriptMove"]["POSITION"].valid())
			std::cout << "WARNING :" << "POSITION" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["SCALE"].valid())
			std::cout << "WARNING :" << "SCALE" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["ROTATION"].valid())
			std::cout << "WARNING :" << "ROTATION" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["SPEED"].valid())
			std::cout << "WARNING :" << "SPEED" << "DataNotBinded\n";
	}
}
void Script_Move::Save(sol::state& lua, GameObject* src)
{
	TransformComponent* temp = (TransformComponent*)src->GetComponent(ComponentId::CT_Transform);
	temp->SetPos(lua["ScriptMove"]["POSITION"]);
	temp->SetScale(lua["ScriptMove"]["SCALE"]);
	temp->SetRotate(lua["ScriptMove"]["ROTATION"]);
	if (DEBUG_LUA)
	{
		if (!lua["ScriptMove"]["POSITION"].valid())
			std::cout << "WARNING :" << "POSITION" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["SCALE"].valid())
			std::cout << "WARNING :" << "SCALE" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["ROTATION"].valid())
			std::cout << "WARNING :" << "ROTATION" << "DataNotBinded\n";
		if (!lua["ScriptMove"]["SPEED"].valid())
			std::cout << "WARNING :" << "SPEED" << "DataNotBinded\n";
	}
}
void Script_Move::Load(sol::state& lua) {
	const auto& my_script = R"(
a = ScriptMove.POSITION
spd = 5
if Input.GetKeyHold("KEYB_W") then
a:SetY( a:GetY() + spd) end
if Input.GetKeyHold("KEYB_A") then
a:SetX( a:GetX() - spd) end
if Input.GetKeyHold("KEYB_S") then
a:SetY( a:GetY() - spd) end
if Input.GetKeyHold("KEYB_D") then
a:SetX( a:GetX() + spd) end
ScriptMove.POSITION = a
	)";
	//ScriptSystem::BindDataCompValues_Runtime();
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "failed to load string-based script in the program" << err.what() << std::endl;
	}
	fx();
}
void Script_Move::Update(double dt) {}

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

Script_Player::Script_Player()
{
	_Name = "ScriptPlayer";
	_DataDep = {
		ToString(ComponentId::CT_Transform),
		ToString(ComponentId::CT_DataPlayer)
	};
}
void Script_Player::Bind(sol::state& lua, GameObject* src) {}
void Script_Player::Save(sol::state& lua, GameObject* src) {}

void Script_Player::Load(sol::state& lua) {
	const auto& my_script = R"(
pos = Table_ScriptPlayer.POSITION
rot = Table_ScriptPlayer.ROTATE
health = Table_ScriptPlayer.HEALTH
healthmax = Table_ScriptPlayer.HEALTHMAX

if Input.GetKeyHold("KEYB_W") then
pos:SetY( a:GetY() + 0.5) end
if Input.GetKeyHold("KEYB_A") then
pos:SetX( a:GetX() - 0.5) end
if Input.GetKeyHold("KEYB_S") then
pos:SetY( a:GetY() - 0.5) end
if Input.GetKeyHold("KEYB_D") then
pos:SetX( a:GetX() + 0.5) end

if Input.GetKeyDown("MOUSE_LBUTTON") then
Table_ScriptPlayer.HEALTH = Table_ScriptPlayer.HEALTH - 0.7
Console.WriteStr("Current Health is : ")
Console.WriteNum(Table_ScriptPlayer.HEALTH)
end

Table_ScriptMove.POSITION = a
	)";

	//ScriptSystem::BindDataCompValues_Runtime();
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "failed to load string-based script in the program" << err.what() << std::endl;
	}
	fx();
}
void Script_Player::Update(double dt) {}