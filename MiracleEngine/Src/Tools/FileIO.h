#pragma once
#include "PrecompiledHeaders.h"

//// IO stuff
//#include <fstream>	// File IO
//#include <iostream>	// Console Shite
//#include <iomanip>	// setw, setprecision
//#include <assert.h>	// Very assertive indeed
////#include <limits>	// std::numeric_limits
//
//// rapidJson stuff
//#include "rapidjson.h"		// J
//#include "document.h"		// S
//#include "writer.h"			// O
//#include "stringbuffer.h"	// N
//#include "error/en.h"		// Json error displaying
////#include <filereadstream.h>	// Stoof
//
//
//// STL stuff
//#include <iterator>	// STL stuff
//#include <string>	// strings
//#include <vector>	// vectors

#define ASSERT(condition) { if(!(condition)) \
{ \
	std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")" << std::endl; \
	FileOut_CrashLog(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)); \
	(_wassert(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0);} \
}

//struct Vec2 {
//	float _x{ 0.0 }, _y{ 0.0 };
//	Vec2() = default;
//};
//
//
//struct Initi {
//	int _ResX{ 0 }, _ResY{ 0 };
//	bool _Fullscreen{ false };
//	Initi() {}
//	~Initi() {}
//};
//
//
//struct Playa {
//
//	Vec2 _Transform;
//	int _HP{ 0 };
//	float _SPD{ 0.0f };
//	std::vector<int> _Weap;
//	bool _Alive{ false };
//};


//	const char* path_player = "./Resources/TextFiles/player.json";
//	const char* path_init = "./Resources/TextFiles/init.json";
//	const char* path_outTest = "./Resources/TextFiles/test.txt";
//	const char* path_crashLog = "./Resources/TextFiles/crashlog.txt";
//}

//struct Initi { // only for taking all input stuff at once
//	int _ResX{ 0 }, _ResY{ 0 };
//	bool _Fullscreen{ false };
//	Initi() {}
//	~Initi() {}
//};	// need move to somewhere in the init stuff




/**
\brief Function to make file input into single char[]
*/
char* FileRead_FileToCharPtr(const char* FileName);
/**
\brief Function to make file input into std::vector<string>
*/
std::vector<std::string> FileRead_FileToStringVector(const char* FileName);
/**
\brief Output to file a crash file with a message
*/
void FileOut_CrashLog(_In_z_ wchar_t const* _Message,
	_In_z_ wchar_t const* _File,
	_In_   unsigned       _Line);

/**
\brief Functions to make allow use of single func to allow different input type
	originally did as template, but kept getting warning of info loss on conversion of int/float to typeT
	and also rapidjson has speciailsed GetXXXX() functions
*/
void JsonDynamicStore(bool& store, rapidjson::Value& val);
void JsonDynamicStore(float& store, rapidjson::Value& val);
void JsonDynamicStore(int& store, rapidjson::Value& val);
void JsonDynamicStore(unsigned int& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<int>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<unsigned int>& store, rapidjson::Value& val);
void JsonDynamicStore(Vector3& store, rapidjson::Value& val);
//void JsonDynamicStore(TransformComponent* store, rapidjson::Value& val, ComponentTypes type);

class ISerial {
public:
	ISerial() = default;
	/*
		Serialize In (json / level)
		Serialize Out (json / level)
	*/
	virtual void SerialInPrefab() {}
	virtual void SerialInLevel() {}
	virtual void SerialOutJson() {}
	virtual void SerialOutText() {}
};