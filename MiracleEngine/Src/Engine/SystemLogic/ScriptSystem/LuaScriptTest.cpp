#include "PrecompiledHeaders.h"
#include "LuaScriptTest.h"




void BindTransform()
{
	
}

void ErrorCheck()
{
	
}

int testfunc() {
		std::cout << "=== running lua code ===" << std::endl;

		//sol::state lua;
		//lua.open_libraries(sol::lib::base,sol::lib::ffi, sol::lib::jit, sol::lib::math);
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io, sol::lib::package, sol::lib::math, sol::lib::table);


		// bind lua funciton to c++ function
		// ------------------------------------------------
		lua.set_function("printa", [&](const std::string str) { std::cout << str << std::endl; });
		lua.set_function("adda", [&](const int x, const int y) { return x + y; });
		pfr = lua.safe_script(R"(
				a = "teststr"
				printa("10")
				printa("abc")
				printa(a)
			)");
		// using table to 'filter' functions
		sol::table table = lua.create_named_table("Console");
		table["WriteLine"] = [&](const std::string str) {std::cout << str << std::endl; };
		pfr = lua.safe_script(R"(
				b = "twostrtest"
				Console.WriteLine("def")
				Console.WriteLine(b)
			)");
		// accessing variables from within lua scripts		lua.script_file("variables.lua");				
		auto err = lua.safe_script(R"(
			config = {
				fullscreen = false,
				resolution = { x = 1024, y = 768 }
			})");
		//err.what();
		// the type "sol::state" behaves exactly like a table
		bool isfullscreen = lua["config"]["fullscreen"]; // can get nested variables
		sol::table config = lua["config"];
		// can also get it using the "get" member function
		// auto replaces the unqualified type name
		auto resolution = config.get<sol::table>("resolution");
		// table and state can have multiple things pulled out of it too
		std::tuple<int, int> xyresolutiontuple = resolution.get<int, int>("x", "y");
		c_assert(std::get<0>(xyresolutiontuple) == 1024);
		c_assert(std::get<1>(xyresolutiontuple) == 768);
		// ------------------------------------------------


//		// load and execute from string
//		lua.script(R"(
//				"a = 'test'"
//			)");
//		// load and execute from file
//		lua.script_file("a_lua_script.lua");
//
//		// run a script, get the result
//		int value = lua.script("return 54");
//		c_assert(value == 54);
//
//		auto bad_code_result = lua.script("123 herp.derp", [](lua_State*, sol::protected_function_result pfr) {
//			// pfr will contain things that went wrong, for either loading or executing the script
//			// Can throw your own custom error
//			// You can also just return it, and let the call-site handle the error if necessary.
//			return pfr;
//			});
//		// it did not work
//		c_assert(!bad_code_result.valid());
//
//		// the default handler panics or throws, depending on your settings
//		// uncomment for explosions:
//		//auto bad_code_result_2 = lua.script("bad.code", &sol::script_default_on_error);

		std::cout << std::endl;

		{
			std::remove("a_lua_script.lua");
		}
		std::cout << "success" << std::endl;

		return 0;
}
