#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"

LuaScriptBase::~LuaScriptBase()
{}

sol::load_result Script_Move::Load(sol::state& lua) {
	const auto& my_script = R"(
Console.WriteStr("SubScript 1\n")
local a = ...
a = 0.4
Table_Data.HEALTH = a
Console.WriteStr("SubScript 1 : ")
Console.WriteNum(a)
	)";
	//ScriptSystem::BindDataCompValues_Runtime();
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "faild to load string-based script in the program" << err.what() << std::endl;
	}
	return fx;
}
void Script_Move::Update(double dt) {
}