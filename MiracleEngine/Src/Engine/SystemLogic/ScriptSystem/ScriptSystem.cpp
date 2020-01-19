#include "PrecompiledHeaders.h"
#include "ScriptSystem.h"

void ScriptSystem::Create_TableScriptData()
{
	_TableScriptData["ScriptMove"] = std::vector<std::string>{ 
		ToString(ComponentId::CT_DataMove)
	};
	lua["Table_ScriptMove"] = lua.create_table();

	_TableScriptData["ScriptPlayer"] = std::vector<std::string>{
		ToString(ComponentId::CT_DataTransform),
		ToString(ComponentId::CT_DataPlayer)
	};
	lua["Table_ScriptPlayer"] = lua.create_table();
} 

void ScriptSystem::Create_Scripts()
{
	_ScriptsAll["ScriptMove"] = new Script_Move{};
	_ScriptsAll["ScriptPlayer"] = new Script_Player{};
}

void ScriptSystem::RunScriptOld(GameObject* src, std::string& scriptName)
{
	mEnvironment = sol::environment{ lua, sol::create, lua.globals() };

	// bind the data
	std::vector<std::string> dataList = _TableScriptData[scriptName];
	IComponent* dataComp = nullptr;
	for (auto itr : dataList)
	{
		dataComp = nullptr;
		// get the DataComponent
		dataComp = (LogicComponent*)src->GetComponent(ToComponentID(itr));
		if (!dataComp)
			std::cout
				<< "WARNING: ScriptSystem::RunScript("
				<< ((IdentityComponent*)(src->GetComponent(ComponentId::CT_Identity)))->ObjectType() << ", "
				<< scriptName << ") has nullptr for 'dataComp'\n";
		// load right table to temp, use
		std::string tableName = "Table_";
		tableName += scriptName; // eg. Table_ScriptMove
		reinterpret_cast<DataComponent*>(dataComp)->BindLuaValues(lua, tableName);
	}
	// bind the script & run (from inside Load())
	_ScriptsAll[scriptName]->Load(lua);
	
	// save the data
	for (auto itr : dataList)
	{
		dataComp = nullptr;
		// get the DataComponent
		dataComp = (LogicComponent*)src->GetComponent(ToComponentID(itr));
		// load right table to temp, use
		std::string tableName = "Table_";
		tableName += scriptName; // Table_DataAmmo || Table_DataHealth || etc
		sol::table temp = lua[tableName];
		reinterpret_cast<DataComponent*>(dataComp)->SaveLuaValues(lua, tableName);
	}

	//		// based on scriptName, use _TableScriptData to get the DataComponent's stuff that needs to bind
//		// once values are binded, run script
//			// script itself will save the things based on the table
//
//		BindDataCompValues_Runtime(lua, src, scriptName);
//			//lua["Table_Data"] = lua.create_table();
//			//lua["Table_Data"]["HEALTH"];
//
//		const auto& my_script = R"(
//	Console.WriteStr("SubScript 1\n")
//	local a = ...
//	a = 0.4
//	Table_Data.HEALTH = a
//	Console.WriteStr("SubScript 1 : ")
//	Console.WriteNum(a)
//		)";
//		sol::load_result fx = lua.load(my_script);
//		if (!fx.valid()) {
//			sol::error err = fx;
//			std::cerr << "failde to load string-based script in the program" << err.what() << std::endl;
//		}
//		fx();
}
void ScriptSystem::RunScript(GameObject* src, std::string& scriptName)
{
	_ScriptsAll[scriptName]->Bind(lua, src);
	_ScriptsAll[scriptName]->Load(lua);
	_ScriptsAll[scriptName]->Save(lua, src);
}

void ScriptSystem::Init() {
	Create_TableScriptData();
	Create_Scripts();
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
		"GetZ", &mathLib::Vector3::GetZ,
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
	if (DEBUG_LUA)
		std::cout << "DEBUG:\t Binding Mouse & Keyboard (KeyUpDownHold) \n";
	Table_Input = lua.create_named_table("Input");
	Table_Input["GetKeyDown"] = [&](const char* str) {
		if (DEBUG_LUA)
			std::cout << "Input.GetKeyDown(" << str << ") ";
		bool temp = _engineSystems._inputSystem->KeyDown(_engineSystems._inputSystem->StringToKeycode(str) );
		if (temp)
		{
			if (DEBUG_LUA)
				std::cout << "Ret::TRUE.\n";
			return true;
		}
		else
		{
			if (DEBUG_LUA)
				std::cout << "Ret::FALSE.\n";
			return false;
		}
	};
	Table_Input["GetKeyHold"] = [&](const char* str) {
		if (DEBUG_LUA)
			std::cout << "Input.GetKeyHold(" << str << ") ";
		bool temp = _engineSystems._inputSystem->KeyHold(_engineSystems._inputSystem->StringToKeycode(str));
		if (temp)
		{
			if (DEBUG_LUA)
				std::cout << "Ret::TRUE.\n";
			return true;
		}
		else
		{
			if (DEBUG_LUA)
				std::cout << "Ret::FALSE.\n";
			return false;
		}
	};
	Table_Input["GetKeyUp"] = [&](const char* str) {
		if (DEBUG_LUA)
			std::cout << "Input.GetKeyUp(" << str << ") ";
		bool temp = _engineSystems._inputSystem->KeyRelease(_engineSystems._inputSystem->StringToKeycode(str));
		if (temp)
		{
			if (DEBUG_LUA)
				std::cout << "Ret::TRUE.\n";
			return true;
		}
		else
		{
			if (DEBUG_LUA)
				std::cout << "Ret::FALSE.\n";
			return false;
		}
	};
}
void ScriptSystem::BindMiscFunctions()
{
	std::cout << "DEBUG:\t Binding Misc Functions (Console) \n";
	Table_Console = lua.create_named_table("Console");
	Table_Console["WriteStr"] = [&](std::string in) {std::cout << in << std::endl; };
	Table_Console["WriteNum"] = [&](double in) {std::cout << in << std::endl; };
	Table_Console["WriteBool"] = [&](bool b) { if (b) std::cout << "TRUE.\n"; else std::cout << "FALSE.\n"; };
	
	std::cout << "DEBUG:\t Binding Misc Functions (Anim) \n";
	Table_Anim = lua.create_named_table("Anim");
	Table_Anim.set_function("Change", [&](std::string in) {
		//AnimationComponent::SetCurrentAnim(in);
	});

		//Table_Console.set_function("WriteLine", [&](std::string in) {std::cout << in << std::endl; });
		//Table_Console.set_function("WriteLine", [&](char* in) {std::cout << in << std::endl; });
		//Table_Console.set_function("WriteLine", [&](int in) {std::cout << in << std::endl; });
		//Table_Console.set_function("WriteLine", [&](double in) {std::cout << in << std::endl; });
	//Table_Console.set_function("WriteLine", sol::overload(
	//	sol::resolve<void(int)>(&ScriptSystem::Print),
	//	sol::resolve<void(std::string)>(&ScriptSystem::Print),
	//	sol::resolve<void(float)>(&ScriptSystem::Print)
	//));
	//Table_Console.set_function("WriteLine", [&](bool in) { if (in) std::cout << "TRUE.\n"; else std::cout << "FALSE.\n"; }); // seems to be causing override problem cause it overrides INT ??

				// lua has a ToString which will ToString a variable
				// in lua have a global variable, then everytime keep ToString in when need to output, then just have a single Table_Console[WriteLine] = {cout << string}

}

void ScriptSystem::Test_DataCompEditing()
{
	std::cout << "========================" << std::endl;
	std::cout << "== running lua code 3 ==" << std::endl;
	// accessing variables from within lua scripts		lua.script_file("variables.lua");				
	pfr = lua.safe_script(R"(
config = {
	fullscreen = false,
	resolution = { x = 1024, y = 768 }
}
testVar = 30

			)");
	if (!pfr.valid())
	{
		sol::error err = pfr;
		std::cout << err.what() << std::endl;
	}
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double var = 0.5;
	std::cout << "var val 1 : " << var << "\n";
	lua["Table_Data"] = lua.create_table();
	lua["Table_Data"]["HEALTH"] = var;

	//lua["test_table"] = lua.create_table_with("HEALTH", &var);
	const auto& my_script = R"(
Console.WriteStr("SubScript 1\n")
local a = ...
a = 0.4
Table_Data.HEALTH = a
Console.WriteStr("SubScript 1 : ")
Console.WriteNum(a)
	)";
	std::cout << "var val 2 : " << var << "\n";
	sol::load_result fx = lua.load(my_script);
	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << "failde to load string-based script in the program" << err.what() << std::endl;
	}
	fx(var); // run script while throwing in values
	double temp = lua["Table_Data"]["HEALTH"];
	std::cout << temp;
	std::cout << "var val 3 : " << temp << "\n";
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "========================" << std::endl;
	std::cout << "++++++++++++++++++++++++" << std::endl;
}
void ScriptSystem::Test_BasicFuncitonality()
{
	std::cout << "========================" << std::endl;
	std::cout << "== running lua code 2 ==" << std::endl;
	Vector3 test;
	pfr = lua.safe_script(R"(
b = "10"
Console.WriteStr("1")
Console.WriteStr("2")
temp = Input.GetKeyDown("MOUSE_LBUTTON")
Console.WriteBool(temp)
Console.WriteStr("3")
Console.WriteStr(b)

test = Vector3.new(4,2,3)
x = test:GetX()
Console.WriteNum(x)
Console.WriteNum(69)

test2 = Transform.new(Vector3.new(7,5,3), Vector3.new(8,6,5), 0.4)
y = test2:GetPosition():GetX()
Console.WriteNum(y)
z = test2:GetScale():GetY()
Console.WriteNum(z)
a = test2:GetRotate()
Console.WriteNum(a)
z = test2:GetScale():GetX()
Console.WriteNum(z)
y = test2:GetPosition():GetZ()
Console.WriteNum(y)
Console.WriteStr("does work")
			)");
	if (!pfr.valid())
	{
		sol::error err = pfr;
		std::cout << err.what() << std::endl;
	}	

	std::cout << "++++++++++++++++++++++++" << std::endl;
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
				Console.WriteStr("def")
				Console.WriteStr(b)
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
	std::cout << "++++++++++++++++++++++++" << std::endl;
	std::cout << "========================" << std::endl;

	return 0;
}
