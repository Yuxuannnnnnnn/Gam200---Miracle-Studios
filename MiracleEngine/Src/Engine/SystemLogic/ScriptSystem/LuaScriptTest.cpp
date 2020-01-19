#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"

LuaScriptBase::~LuaScriptBase()
{}

void Script_Move::Load(sol::state& lua) {
	const auto& my_script = R"(
a = Table_ScriptMove.POSITION
spd = Table_ScriptMove.SPEED
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