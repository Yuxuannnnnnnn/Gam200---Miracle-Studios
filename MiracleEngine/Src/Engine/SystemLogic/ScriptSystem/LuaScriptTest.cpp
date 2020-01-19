#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"

Script_Move::Script_Move()
{
	_Name = "ScriptMove";
	_DataDep = { "Transform" };
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
	lua["Table_ScriptMove"]["POSITION"] = temp->GetPos();
	lua["Table_ScriptMove"]["SCALE"] = temp->GetScale();
	lua["Table_ScriptMove"]["ROTATION"] = temp->GetRotate();
	DataPlayerComponent* temp1 = (DataPlayerComponent*)src->GetComponent(ComponentId::CT_DataPlayer);
	lua["Table_ScriptMove"]["SPEED"] = &temp1->_MovementSpeed;
	if (0)
	{
		if (!lua["Table_ScriptMove"]["POSITION"].valid())
			std::cout << "WARNING :" << "POSITION" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["SCALE"].valid())
			std::cout << "WARNING :" << "SCALE" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["ROTATION"].valid())
			std::cout << "WARNING :" << "ROTATION" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["SPEED"].valid())
			std::cout << "WARNING :" << "SPEED" << "DataNotBinded\n";
	}
}
void Script_Move::Save(sol::state& lua, GameObject* src)
{
	if (0)
	{
		if (!lua["Table_ScriptMove"]["POSITION"].valid())
			std::cout << "WARNING :" << "POSITION" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["SCALE"].valid())
			std::cout << "WARNING :" << "SCALE" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["ROTATION"].valid())
			std::cout << "WARNING :" << "ROTATION" << "DataNotBinded\n";
		if (!lua["Table_ScriptMove"]["SPEED"].valid())
			std::cout << "WARNING :" << "SPEED" << "DataNotBinded\n";
	}
	TransformComponent* temp = (TransformComponent*)src->GetComponent(ComponentId::CT_Transform);
	temp->SetPos(lua["Table_ScriptMove"]["POSITION"]);
	temp->SetScale(lua["Table_ScriptMove"]["SCALE"]);
	temp->SetRotate(lua["Table_ScriptMove"]["ROTATION"]);
	DataPlayerComponent* temp1 = (DataPlayerComponent*)src->GetComponent(ComponentId::CT_DataPlayer);
	//temp1->_MovementSpeed = lua["Table_ScriptMove"]["SPEED"];
}
void Script_Move::Load(sol::state& lua) {
	const auto& my_script = R"(
-- a = Table_ScriptMove.POSITION
-- spd = Table_ScriptMove.SPEED
-- if Input.GetKeyHold("KEYB_W") then
-- a:SetY( a:GetY() + spd) end
-- if Input.GetKeyHold("KEYB_A") then
-- a:SetX( a:GetX() - spd) end
-- if Input.GetKeyHold("KEYB_S") then
-- a:SetY( a:GetY() - spd) end
-- if Input.GetKeyHold("KEYB_D") then
-- a:SetX( a:GetX() + spd) end
-- Table_ScriptMove.POSITION = a

a = Table_ScriptMove.POSITION
spd = 5
if Input.GetKeyHold("KEYB_W") then
a:SetY( a:GetY() + spd) end
if Input.GetKeyHold("KEYB_A") then
a:SetX( a:GetX() - spd) end
if Input.GetKeyHold("KEYB_S") then
a:SetY( a:GetY() - spd) end
if Input.GetKeyHold("KEYB_D") then
a:SetX( a:GetX() + spd) end
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
void Script_Move::Update(double dt) {}

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

Script_Player::Script_Player()
{
	_Name = "ScriptPlayer";
	_DataDep = { "Transform", "DataPlayer" };
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

	sol::object v = lua["pos"];
	if (v.valid() && DEBUG_LUA)
		std::cout << "hi";

	//ScriptSystem::BindDataCompValues_Runtime();
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "failed to load string-based script in the program" << err.what() << std::endl;
	}
	fx();
}
void Script_Player::Update(double dt) {}