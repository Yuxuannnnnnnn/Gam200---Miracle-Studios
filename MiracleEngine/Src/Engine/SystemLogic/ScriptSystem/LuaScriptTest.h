#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <lua/lua.h>

class LuaScriptBase {
public:
	std::string _Name;
	std::vector<std::string> _DataDep;
public:
	LuaScriptBase() = default;
	virtual ~LuaScriptBase() = default;
	virtual void Bind(sol::state& lua, GameObject* src) = 0;
	virtual void Save(sol::state& lua, GameObject* src) = 0;
	virtual void Load(sol::state& lua) = 0;
	virtual void Update(double dt) = 0;
};

class Script_Move : public LuaScriptBase {
public:
	Script_Move();
	~Script_Move() = default;
	virtual void Bind(sol::state& lua, GameObject* src);
	virtual void Save(sol::state& lua, GameObject* src);
	virtual void Load(sol::state& lua) override;
	virtual void Update(double dt) override;
};

class Script_Player : public LuaScriptBase {
public:
	Script_Player();
	~Script_Player() = default;
	virtual void Bind(sol::state& lua, GameObject* src);
	virtual void Save(sol::state& lua, GameObject* src);
	virtual void Load(sol::state& lua) override;
	virtual void Update(double dt) override;
};