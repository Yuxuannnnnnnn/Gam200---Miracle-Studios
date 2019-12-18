#include "PrecompiledHeaders.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <sol/assert.hpp> // note need to remove this, i dont think this is allowed for public use
#include <lua/lua.h>
//#include <lua/lualib.h>
//#define SOL_USING_CXX_LUA_JIT



int testfunc() {
		std::cout << "=== running lua code ===" << std::endl;
		 
		{
			std::ofstream out("a_lua_script.lua");
			out << "print('hi from a lua script file')";
		}

		sol::state lua;
		lua.open_libraries(sol::lib::base);

		// load and execute from string
		lua.script("a = 'test'");
		// load and execute from file
		lua.script_file("a_lua_script.lua");

		// run a script, get the result
		int value = lua.script("return 54");
		c_assert(value == 54);

		auto bad_code_result = lua.script("123 herp.derp", [](lua_State*, sol::protected_function_result pfr) {
			// pfr will contain things that went wrong, for either loading or executing the script
			// Can throw your own custom error
			// You can also just return it, and let the call-site handle the error if necessary.
			return pfr;
			});
		// it did not work
		c_assert(!bad_code_result.valid());

		// the default handler panics or throws, depending on your settings
		// uncomment for explosions:
		//auto bad_code_result_2 = lua.script("bad.code", &sol::script_default_on_error);

		std::cout << std::endl;

		{
			std::remove("a_lua_script.lua");
		}
		std::cout << "success" << std::endl;

		return 0;
}
