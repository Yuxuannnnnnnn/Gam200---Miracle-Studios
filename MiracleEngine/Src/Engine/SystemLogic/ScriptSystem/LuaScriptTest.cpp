#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"

LuaScriptBase::~LuaScriptBase()
{}

void Script_Move::Load(sol::state& lua) {
	const auto& my_script = R"(
Console.WriteStr("SubScript 1\n")
a = Table_ScriptMove.POSITION
a:SetX( a:GetX() + 0.05)
Table_ScriptMove.POSITION = a
Input.GetKeyHold("MOUSE_LBUTTON")
	)";
	//ScriptSystem::BindDataCompValues_Runtime();
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "faild to load string-based script in the program" << err.what() << std::endl;
	}
	fx();
}
void Script_Move::Update(double dt) {
}