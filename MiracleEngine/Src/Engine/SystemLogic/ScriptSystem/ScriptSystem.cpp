#include "PrecompiledHeaders.h"
#include "ScriptSystem.h"

void ScriptSystem::Create_TableScriptData()
{
	_TableScriptData["health"] = std::vector<std::string>{ "health" };
	_TableScriptData["ammo"] = std::vector<std::string>{ "ammo" };
	_TableScriptData["shield"] = std::vector<std::string>{ "capacity", "recharge" };
}

void ScriptSystem::RunScript(GameObject* src, std::string& scriptName)
{

}

void ScriptSystem::Init() {
	Create_TableScriptData();
	BindAll();
}
//void ScriptSystem::Update(float dt) {}
void ScriptSystem::Exit() {

}

void ScriptSystem::BindAll()
{
	BindTransform();
	BindMathVector2();
	BindMathVector3();
	BindMouseAndKeyboard();
	BindMiscFunctions();
}

void ScriptSystem::BindTransform()
{
	std::cout << "DEBUG:\t Binding TransformComponent \n";
	lua.new_usertype <TransformComponent>("Transform",
		// Constructor 
		sol::constructors <
		TransformComponent(),
		TransformComponent(const Vector3 & pos, const Vector3 & scale, const float& angle)
		>(),
		// Data Members
		"GetPosition", &TransformComponent::GetPos,
		"SetPosition", &TransformComponent::SetPos,
		"GetScale", &TransformComponent::GetScale,
		"SetScale", &TransformComponent::SetScale,
		"GetRotate", &TransformComponent::GetRotate,
		"SetRotate", &TransformComponent::SetRotate
		);
}
void ScriptSystem::BindMathVector2()
{
	std::cout << "DEBUG:\t Binding Math::Vec2 \n";
	lua.new_usertype<mathLib::Vector2>("Vector2",
		// Constructor 
		sol::constructors<
		mathLib::Vector2(),
		mathLib::Vector2(const float, const float),
		mathLib::Vector2(float, float),
		mathLib::Vector2(const Vector2&)
		>(),
		// Data Members
		"x", &mathLib::Vector2::_x,
		"y", &mathLib::Vector2::_y,

		// Member Functions
		"GetX", &mathLib::Vector2::GetX,
		"GetY", &mathLib::Vector2::GetY,
		"SetX", &mathLib::Vector2::SetX,
		"SetY", &mathLib::Vector2::SetY,
		"Get", &mathLib::Vector2::Set,

		"Sum", &mathLib::Vector2::Sum,
		"Distance", sol::overload(
			sol::resolve<float(const Vector2 & pt)const>(&mathLib::Vector2::Distance),
			sol::resolve<float(float x, float y)const>(&mathLib::Vector2::Distance)
		),
		"Length", &mathLib::Vector2::Length,
		"SquaredLength", &mathLib::Vector2::SquaredLength,
		"Normalize", &mathLib::Vector2::Normalize,
		"Normalized", &mathLib::Vector2::Normalized,
		"Round", &mathLib::Vector2::Round,
		"Rounded", &mathLib::Vector2::Rounded,
		"Cross", &mathLib::Vector2::Cross,
		"Dot", &mathLib::Vector2::Dot,
		"AbsDot", &mathLib::Vector2::AbsDot,
		"Abs", &mathLib::Vector2::Abs,
		"IsFinite", &mathLib::Vector2::IsFinite,
		// Operator Overloading
		sol::meta_function::addition, sol::resolve<mathLib::Vector2(const mathLib::Vector2&, const mathLib::Vector2&)>(mathLib::operator+),
		sol::meta_function::multiplication, sol::overload(
			sol::resolve<mathLib::Vector2(const Vector2 & lhs, const float& rhs)>(mathLib::operator*),
			sol::resolve<mathLib::Vector2(const float& lhs, const Vector2 & rhs)>(mathLib::operator*)
		),
		sol::meta_function::subtraction, sol::resolve<mathLib::Vector2(const mathLib::Vector2&, const mathLib::Vector2&)>(mathLib::operator-),
		sol::meta_function::division, sol::overload(
			sol::resolve<mathLib::Vector2(const Vector2 & lhs, const float& rhs)>(mathLib::operator/),
			sol::resolve<mathLib::Vector2(const Vector2 & lhs, const Vector2 & rhs)>(mathLib::operator/)
		),
		sol::meta_function::equal_to, sol::resolve<bool(const Vector2 & lhs, const Vector2 & rhs)>(mathLib::operator==)
		);
}
void ScriptSystem::BindMathVector3()
{
	sol::base_classes, sol::base<IComponent>();
	std::cout << "DEBUG:\t Binding Math::Vec3 \n";
	lua.new_usertype<mathLib::Vector3>("Vector3",
		// Constructor 
		sol::constructors<
		mathLib::Vector3(),
		mathLib::Vector3(const float, const float),
		mathLib::Vector3(float, float, float),
		mathLib::Vector3(const Vector3&)
		>(),

		// Data Members
		"x", &mathLib::Vector3::_x,
		"y", &mathLib::Vector3::_y,
		"z", &mathLib::Vector3::_z,

		// Member Functions
		"GetX", &mathLib::Vector3::GetX,
		"GetY", &mathLib::Vector3::GetY,
		"GetZ", &mathLib::Vector3::SetZ,
		"SetX", &mathLib::Vector3::SetX,
		"SetY", &mathLib::Vector3::SetY,
		"SetZ", &mathLib::Vector3::SetZ,
		"Get", &mathLib::Vector3::Set,

		"Sum", &mathLib::Vector3::Sum,
		"Distance", sol::overload(
			sol::resolve<float(const Vector3 & pt)const>(&mathLib::Vector3::Distance),
			sol::resolve<float(float x, float y, float z)const>(&mathLib::Vector3::Distance)
		),
		"Length", &mathLib::Vector3::Length,
		"SquaredLength", &mathLib::Vector3::SquaredLength,
		"Normalize", &mathLib::Vector3::Normalize,
		"Normalized", &mathLib::Vector3::Normalized,
		"Round", &mathLib::Vector3::Round,
		"Rounded", &mathLib::Vector3::Rounded,
		"Cross", &mathLib::Vector3::Cross,
		"Dot", &mathLib::Vector3::Dot,
		"AbsDot", &mathLib::Vector3::AbsDot,
		"Abs", &mathLib::Vector3::Abs,
		"IsFinite", &mathLib::Vector3::IsFinite,
		// Operator Overloading
		sol::meta_function::addition, sol::overload(
			sol::resolve<mathLib::Vector3(const mathLib::Vector3&)>(mathLib::operator+),
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const Vector3 & rhs)>(mathLib::operator+)
		),
		sol::meta_function::subtraction, sol::overload(
			sol::resolve<mathLib::Vector3(const mathLib::Vector3&)>(mathLib::operator-),
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const Vector3 & rhs)>(mathLib::operator-)
		),
		sol::meta_function::multiplication, sol::overload(
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const Vector3 & rhs)>(mathLib::operator*),
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const float& rhs)>(mathLib::operator*),
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const float& rhs)>(mathLib::operator*)
		),
		sol::meta_function::division, sol::overload(
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const float& rhs)>(mathLib::operator/),
			sol::resolve<mathLib::Vector3(const Vector3 & lhs, const Vector3 & rhs)>(mathLib::operator/)
		),
		sol::meta_function::equal_to, sol::resolve<bool(const Vector3 & lhs, const Vector3 & rhs)>(mathLib::operator==)
		);
}
void ScriptSystem::BindMouseAndKeyboard()
{
	std::cout << "DEBUG:\t Binding Mouse & Keyboard (KeyUpDownHold) \n";
	Table_Input = lua.create_named_table("Input");
	Table_Input["GetKeyDown"] = [&](const char* str) {
		std::cout << "Input.GetKeyDown : " << str << " ";
		bool temp = EngineSystems::GetInstance()._inputSystem->KeyDown(
			EngineSystems::GetInstance()._inputSystem->StringToKeycode(str) );
		if (temp == true)
		{
			std::cout << "true.\n";
			return true;
		}
		else
		{
			std::cout << "false.\n";
			return false;
		}
	};
	Table_Input["GetKeyHold"] = [&](const char* str) {
		std::cout << "Input.GetKeyHold : " << str << " ";
		bool temp = EngineSystems::GetInstance()._inputSystem->KeyHold(
			EngineSystems::GetInstance()._inputSystem->StringToKeycode(str));
		if (temp == true)
		{
			std::cout << "true.\n";
			return true;
		}
		else
		{
			std::cout << "false.\n";
			return false;
		}
	};
	Table_Input["GetKeyUp"] = [&](const char* str) {
		std::cout << "Input.GetKeyUp : " << str << " ";
		bool temp = EngineSystems::GetInstance()._inputSystem->KeyRelease(
			EngineSystems::GetInstance()._inputSystem->StringToKeycode(str));
		if (temp == true)
		{
			std::cout << "true.\n";
			return true;
		}
		else
		{
			std::cout << "false.\n";
			return false;
		}
	};
}
void ScriptSystem::BindMiscFunctions()
{
	std::cout << "DEBUG:\t Binding Misc Functions (Console) \n";
	Table_Console = lua.create_named_table("Console");
	Table_Console["WriteLine"] = [&](const std::string str) {std::cout << "Console.Writeline : " << str << std::endl; };
	//Table_Console["WriteLine"] = [&](const bool b) {std::cout << b << std::endl; };
	//need do sol::overload for "WriteLine"
}


void ScriptSystem::TestFunctionNew()
{
	std::cout << "========================" << std::endl;
	std::cout << "== running lua code 2 ==" << std::endl;

	pfr = lua.safe_script(R"(
b = "10"
Console.WriteLine("1")
Console.WriteLine("2")
temp = Input.GetKeyDown("MOUSE_LBUTTON")
Console.WriteLine("3")
			)");
	if (!pfr.valid())
	{
		sol::error err = pfr;
		std::cout << err.what() << std::endl;
	}
		

	std::cout << "========================" << std::endl;
	std::cout << "========================" << std::endl;
}

int ScriptSystem::testfunc() {
	std::cout << "========================" << std::endl;
	std::cout << "=== running lua code ===" << std::endl;

	//sol::state lua;
	//lua.open_libraries(sol::lib::base,sol::lib::ffi, sol::lib::jit, sol::lib::math);


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
//	sol::table table = lua.create_named_table("Console");
//	table["WriteLine"] = [&](const std::string str) {std::cout << "Console.Writeline : " << str << std::endl; };
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

	BindTransform();

	std::cout << "success" << std::endl;
	std::cout << "========================" << std::endl;
	std::cout << "========================" << std::endl;

	return 0;
}
