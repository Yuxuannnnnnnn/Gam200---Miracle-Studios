#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <lua/lua.h>

class LuaScriptBase {
public:
	LuaScriptBase() = default;
	virtual ~LuaScriptBase();
	virtual sol::load_result Load(sol::state& lua) = 0;
	virtual void Update(double dt) = 0;
};

class Script_Move : public LuaScriptBase {
public:
	Script_Move() = default;
	~Script_Move() = default;

	virtual sol::load_result Load(sol::state& lua) override;
	virtual void Update(double dt) override;
};
