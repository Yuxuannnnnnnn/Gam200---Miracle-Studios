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

#include "MathLib/Vector3.h"

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

	Playa() {}
	~Playa() {}
	Playa(const Playa& rhs) = delete;
	Playa& operator= (const Playa& rhs) = delete;

	void Print() {
		std::cout
			<< "Trans: " << _Transform._x << " " << _Transform._y << std::endl
			<< "HP: " << _HP << std::endl
			<< "SPD: " << _SPD << std::endl
			<< "ALIVE: " << _Alive << std::endl
			<< "Weaps:";
		std::vector<int>::iterator itr = _Weap.begin();
		while (itr != _Weap.end())
			std::cout << *itr++;
		std::cout << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, Playa& player) {
		os << "{\n"
			<< "\t\"Health\": " << player._HP << ",\n"
			<< "\t\"Speed\": " << player._SPD << ",\n"
			<< "\t\"Weapons\": [";
		std::vector<int>::iterator itr = player._Weap.begin();
		while (itr != player._Weap.end())
		{
			os << *itr++;
			if (itr != player._Weap.end())
				os << ',';	// note for actual use, the array cannot have the trailing ','
		}
		os << "],\n"
			<< "\t\"Alive\": " << (player._Alive ? "true" : "false") << '\n'
			<< '}';
		return os;
	}
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
\brief Read BASE-STATS for PLAYER
		Will get following values:
		- HP		int
		- Speed		float
		- Weapon	std::vector
		- Alive		bool
*/
void FileRead_PlayerInfo(Playa& player);
/**
\brief Output to file a crash file with a message
*/
void FileOut_CrashLog(const char *msg);
/**
\brief WIP: Output player in json format
*/
void FileOut_PlayerInfo(Playa& player);

void JsonDynamicStore(bool& store, rapidjson::Value& val);
void JsonDynamicStore(float& store, rapidjson::Value& val);
void JsonDynamicStore(int& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<int>& store, rapidjson::Value& val);
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val);
void JsonDynamicStore(Vector3& store, rapidjson::Value& val);

// collection of previous nonsense below

//void OldFileRead_AppInit() // Func to read initialization file
//{
//	std::ifstream _file; // the input stream
//	_file.open("input1.txt", std::ios_base::in | std::ios_base::binary);
//	if (!_file.is_open()) // file cannot be opened
//	{
//		std::cout << "! WARNING !! Using default start parameters!!!\n";
//		_ResX = 1280; _ResY = 720; _Fullscreen = false;
//	}
//	else // read info from file
//	{
//		// 'global' varibles
//		int arrElement[MAX_ARR_SIZE] = { 0 };
//		std::string arrKey[MAX_ARR_SIZE];
//		int count = 0; // for use in storing elements into arrays
//
//		while (!_file.eof()) // while not eof
//		{
//			std::string line;
//			std::queue<int> queNum;
//			int pos = 0; // for substr position
//
//			getline(_file, line);
//			for (std::string::iterator itr = line.begin(); itr != line.end(); ++itr) {
//				// FIND mapKey
//				++pos; // find position of first non-alphabet, while counting cause need position
//				if (!AsciiLetterCheck(*itr))
//					arrKey[count] = line.substr(0, --pos);
//				// FIND mapElement
//				if (AsciiNumberCheck(*itr)) // only allow '.' and ASCII numbers
//					queNum.push(*itr);
//			}
//			// calc actual value stored in Queue
//			while (queNum.size()) {
//				int mult = MultTen(static_cast<int>(queNum.size())); // using MultTen to get the 1XXXX multiplier
//				int val = queNum.front() - 48; // -48 cause ASCII
//				queNum.pop();
//				val *= mult;
//				arrElement[count] += val;
//			}
//			++count;
//			pos = 0;
//		}
//
//		// cout all varibles
//		for (int i = 0; i < MAX_ARR_SIZE; ++i)
//			std::cout << arrKey[i] << " " << arrElement[i] << '\n';
//		std::cout << '\n';
//		// TODO save all data into a MAP
//	}
//
//	// cout windows settings for debug
//		//std::cout << "- DEBUG --       ResX = " << _ResX << "\n";
//		//std::cout << "- DEBUG --       ResY = " << _ResY << "\n";
//		//std::cout << "- DEBUG -- FullScreen = " << _Fullscreen<< "\n";
//
//		// proceed to call Windows_Init()
//		// OR
//		// exit function so Windows_Init can execute
//
//	return;
//}
//// cannot pass Document as * or &, have to use in actual function
//rapidjson::Document NotWorking_FileRead_FileToDoc(const char* FileName)
//{
//	// open file
//	std::fstream _file;
//	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
//	if (_file.is_open()) // file cannot be opened
//	{
//		// read file
//		char* iBuffer = new char[MAX_CHAR_ARR_BUFFER];
//		int count = 0;
//		while ((_file.good() || count == MAX_CHAR_ARR_BUFFER))
//		{
//			char c = _file.get();
//			if (jsonParseChecker(c))
//			{
//				iBuffer[count] = c;
//				++count;
//			}
//		}
//		iBuffer[count] = '\0';
//
//		rapidjson::Document d;
//		rapidjson::StringStream strem(iBuffer);
//
//		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
//		if (d.Parse(iBuffer).HasParseError()) {
//			fprintf(stderr, "\nError(offset %u): %s\n",
//				(unsigned)d.GetErrorOffset(),
//				rapidjson::GetParseError_En(d.GetParseError()));
//		}
//		return d;
//	}
//	std::cout << "! WARNING !! File Cannot Open!!!\n";
//	return nullptr;
//}
//rapidjson::Document NotWorking_FileRead_ParseToDoc(char* src)
//{
//	rapidjson::Document d;
//	rapidjson::StringStream strem(src);
//	//const char works[] = " { \"ResX\" : 1 , \"ResY\" : 2 , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
//	//d.Parse(works); // this parsing from string literal got no problem
//	d.Parse<rapidjson::kParseStopWhenDoneFlag>(src); // kParseStopWhenDoneFlag supresses the Parsing error
//	if (d.Parse(src).HasParseError()) { // this shows the parsing error
//		fprintf(stderr, "\nError(offset %u): %s\n",
//			(unsigned)d.GetErrorOffset(),
//			rapidjson::GetParseError_En(d.GetParseError()));
//	}
//	return d;
//}