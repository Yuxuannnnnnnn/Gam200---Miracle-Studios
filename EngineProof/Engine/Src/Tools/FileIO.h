#pragma once
// IO stuff
#include <fstream>	// File IO
#include <iostream>	// Console Shite
#include <iomanip>	// setw, setprecision
#include <assert.h>	// Very assertive indeed
//#include <limits>	// std::numeric_limits

// rapidJson stuff
#include "rapidjson/rapidjson.h"		// J
#include "rapidjson/document.h"		// S
#include "rapidjson/writer.h"			// O
#include "rapidjson/stringbuffer.h"	// N
#include "rapidjson/error/en.h"		// Json error displaying
//#include <filereadstream.h>	// Stoof

#include "MathLib/SYMath.h"

// STL stuff
#include <iterator>	// STL stuff
#include <string>	// strings
#include <vector>	// vectors
#include <map>		// use for keyword storing
//#include <queue>	// Queue for storing input
//#include <algorithm>// foreach



//prints error output to the cnosole
//FileOut_CrashLog::prints error output to the crashlog.txt
//_wassert:: prints an error message box 

#define ASSERT(condition) { if(!(condition)) \
{ \
	std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")" << std::endl; \
	FileOut_CrashLog(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)); \
	(_wassert(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0);} \
}


struct Vec2 {
	float _x{ 0.0 }, _y{ 0.0 };
	Vec2() = default;
};
struct Initi {
	int _ResX{ 0 }, _ResY{ 0 };
	bool _Fullscreen{ false };
	Initi() {}
	~Initi() {}
};
struct TempGO {
	int id{ 0 };
	Vector3 pos{ Vector3() };
	Vector3 scale{ Vector3() };
	float rot{ 0.0f };
	TempGO() {}
	~TempGO() {}
};

/**
\brief Function to make file input into single char[]
*/
char* FileRead_FileToCharPtr(const char* FileName);

/**
\brief Read start up info for application
		Will get following values:
		- Resolution (X, Y)
		- Fullscreen On/Off
*/
void FileRead_StartUp(Initi& initialise);

/**
\brief Output to file a crash file with a message
*/
void FileOut_CrashLog(_In_z_ wchar_t const* _Message,
	_In_z_ wchar_t const* _File,
	_In_   unsigned       _Line);

void JsonDynamicStore(bool& store, rapidjson::Value& val);
void JsonDynamicStore(float& store, rapidjson::Value& val);
void JsonDynamicStore(int& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<int>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val);
void JsonDynamicStore(Vector3& store, rapidjson::Value& val);