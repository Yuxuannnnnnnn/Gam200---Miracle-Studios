#pragma once
#include "PrecompiledHeaders.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <sol/assert.hpp> // note need to remove this, i dont think this is allowed for public use
#include <lua/lua.h>
//#include <lua/lualib.h>
//#define SOL_USING_CXX_LUA_JIT
#include <string>

void BindTransform();

int testfunc();

static sol::state lua; // replace with the one in ScriptSYS
static sol::protected_function_result pfr;
class LuaScriptComponent;

class ScriptSystem// : public ISystem
{
public:
	//--------------------------------------------------
	ScriptSystem()
		: mbSceneScriptsLoaded{ false }, mnScriptsLoaded{ 0 }
	{
		// Create a log file.
		//log.CreateLogFile("log/script_debug_log.txt");
	}
	~ScriptSystem() = default;
	virtual void Init();
	virtual void Update(float dt);
	virtual void Exit() {}

	void PausedUpdate(float dt);
	//--------------------------------------------------

	// Get number of scripts loaded.
	int GetLoadedScriptCount() const { return mnScriptsLoaded; }

	// Binds sol::function to functions in Lua
	void BindAIStateFunctions(LuaScriptComponent* script);
	//void BindCameraFunctions(LuaScriptComponent* script);
	friend class Editor;
	friend class Factory;

	static sol::state lua;	// The Lua State
	sol::table math_table;
	sol::table console_table;
private:
	//FileLogger log;		// Logger specific to this scripting system.
	// Loads all the scripts in a scene.
	void LoadSceneScripts();
	// Whether scripts are loaded in the scene.
	bool mbSceneScriptsLoaded{ false };
	// Run all loaded script in the scene.
	void RunSceneScripts(float dt);

	template<typename T, typename = std::enable_if<!std::is_pointer<T>::value>::type>
	inline void SetLuaGlobalVariable(const char* var_name, const T * ptr);

	int mnScriptsLoaded;	// Number of scripts loaded
};