
// IO stuff
#include <fstream>	// File IO
#include <iostream>	// Console Shite
#include <iomanip>	// setw, setprecision
#include <assert.h>	// Very assertive indeed
//#include <limits>	// std::numeric_limits

// rapidJson stuff
#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying
//#include <filereadstream.h>	// Stoof


// STL stuff
#include <iterator>	// STL stuff
#include <string>	// strings
#include <vector>	// vectors
//#include <map>		// use for keyword storing
//#include <queue>	// Queue for storing input
//#include <algorithm>// foreach


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


struct Playa {

	Vec2 _Transform;
	int _HP{ 0 };
	float _SPD{ 0.0f };
	std::vector<int> _Weap;
	bool _Alive{ false };
};


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
\brief Functions to make allow use of single func to allow different input type
	originally did as template, but kept getting warning of info loss on conversion of int/float to typeT
*/
void JsonDynamicStore(bool& store, rapidjson::Value& val);
void JsonDynamicStore(float& store, rapidjson::Value& val);
void JsonDynamicStore(int& store, rapidjson::Value& val);
void JsonDynamicStore(unsigned int& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<int>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<unsigned int>& store, rapidjson::Value& val);
void JsonDynamicStore(Vector3&store, rapidjson::Value& val);
//void JsonDynamicStore(TransformComponent* store, rapidjson::Value& val, ComponentTypes type);

/**
\brief Function to make file input into single char[]
*/
char* FileRead_FileToCharPtr(const char* FileName);
/**
\brief Function to make file input into std::vector<string>
*/
std::vector<std::string>& FileRead_FileToStringVector(const char* FileName);

/**
\brief Read start up info for application
		Will get following values:
		- Resolution (X, Y)
		- Fullscreen On/Off
*/
//void FileRead_StartUp(Initi& initialise);

/**
\brief Read BASE-STATS for PLAYER
		Will get following values:
		- HP		int
		- Speed		float
		- Weapon	std::vector
		- Alive		bool
*/
//void FileRead_Player(Player* player);
/**
\brief WIP: Output player in json format
*/
//void FileOut_PlayerInfo(Playa& player);

/**
\brief Output to file a crash file with a message
*/
//void FileOut_CrashLog(const char* msg);