#include "FileIO.h"

#define MAX_CHAR_ARR_BUFFER 1000
//#define ASSERT(condition) { if((condition)){ std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")" << std::endl; (_wassert(_CRT_WIDE(#condition), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0);} }

namespace FilePathNames {
	const char* path_player = "./Resources/TextFiles/player.json";
	const char* path_init = "./Resources/TextFiles/init.json";
	const char* path_outTest = "./Resources/TextFiles/test.txt";
	const char* path_crashLog = "./Resources/TextFiles/crashlog.txt";
}

//Data - driven means serialized(Data saving / loading).
//Configurationand tweaking data means a config data file 
//where you can load general game application info(e.g.windowresolution).
//Game objects are not data - driven using factories.
//Data - driven means serialized(Data saving / loading).

// take in power, x10 by power amt
int MultTen(int power)
{
	int val = 1;
	while (--power)
		val *= 10;
	return val;
}
bool AsciiLetterCheck(const char c) 
{
	// 'A'&'Z' || 'a'&'z'
	return (c > 64 && c < 91 || c > 96 && c < 123) ? true : false;
}
bool AsciiNumberCheck(const char c)
{	
	return (c > 47 && c < 58) ? true : false; // 0 to 9
}
int AsciiNumberCovert(const char c)
{
	// -48 cause ASCII
	return c - 48;
}
/**
\brief Function to use to allow parsing of all relevant json elements
*/
bool jsonParseChecker(const char c)
{
	if (AsciiNumberCheck(c) ||
		AsciiLetterCheck(c) ||
		c == '\"' || c == ',' ||
		c == ':'|| c == '.' ||
		c == '{' || c == '}' ||
		c == '[' || c == ']'
		)
		return true;
	return false;
}

/**
\brief Functions to make allow use of single func to allow different input type
	originally did as template, but kept getting warning of info loss on conversion of int/float to typeT
*/
void JsonDynamicStore(bool& store, rapidjson::Value &val)
{
	if (typeid(store).name() == typeid(bool).name())
		store = static_cast<bool>(val.GetBool());
	return;
}
void JsonDynamicStore(float& store, rapidjson::Value& val)
{
	if (typeid(store).name() == typeid(float).name())
		store = static_cast<float>(val.GetFloat());
}
void JsonDynamicStore(int& store, rapidjson::Value& val)
{
	if (typeid(store).name() == typeid(int).name())
		store = static_cast<int>(val.GetInt());
}
void JsonDynamicStore(std::vector<int> &store, rapidjson::Value& val)
{
	if (val.IsArray()) // check to ensure that the 'val' is also an array
		for (unsigned i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetInt());
	return;
}
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val)
{
	if (val.IsArray())
		for (unsigned i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetFloat());
	return;
}
void JsonDynamicStore(Vector3& store, rapidjson::Value& val)
{
	if (val.IsArray())
	{
		Vector3 tempVec(val[0].GetFloat(), val[1].GetFloat(), 1);
		store = tempVec;
	}
}

/**
\brief Function to make file input into single char[]
*/
char* FileRead_FileToCharPtr(const char* FileName)
{
	// open file
	std::fstream _file;
	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
	if (_file.is_open())
	{
		// read file
		char* iBuffer = new char[MAX_CHAR_ARR_BUFFER];
		int count = 0;
		while ((_file.good() || count == MAX_CHAR_ARR_BUFFER))
		{
			char c = static_cast<char>(_file.get());
			if (jsonParseChecker(c))
			{
				iBuffer[count] = c;
				++count;
			}
		}
		iBuffer[count] = '\0';
		_file.close();
		return iBuffer;
	}
	std::cout << "! WARNING !! File Cannot Open!!!\n";
	return nullptr;
}

/**
\brief Function to make file input into single char[]
*/
void FileRead_Level(const char* FileName)
{
	std::fstream _file;
	//_file.open(FileName, std::ios_base::in | std::ios_base::binary);

	//std::string objectArchetype;
	//Vec2 objectPosition;
	//float objectRotation;

//------------------------------------------------------

	//std::fstream _file;
	_file.open(FileName, std::ios_base::in | std::ios_base::binary);

	std::map <std::string , std::vector<Transform*>> dill;

	if (_file.is_open())
	{
		// each loop read 4 lines, Type Pos Scale Rot
		// find 



		// read file
		char* iBuffer = new char[MAX_CHAR_ARR_BUFFER];
		int count = 0;
		while ((_file.good()))
		{
			_file.getline(iBuffer,'\n');
			if (count == MAX_CHAR_ARR_BUFFER)
			{
				std::cout << "MAX_CHAR_ARR_BUFFER REACHED!!!!!!!!!!!!!\n";
				break;
			}
			char c = static_cast<char>(_file.get());
			if (jsonParseChecker(c))
			{
				iBuffer[count] = c;
				++count;
			}
		}
		iBuffer[count] = '\0';
		_file.close();
	}
	std::cout << "! WARNING !! File Cannot Open!!!\n";
	return;
}

/**
\brief Read start up info for application
		Will get following values:
		- Resolution (X, Y)
		- Fullscreen On/Off
*/
void FileRead_StartUp(Initi& initialise)
{
	std::cout << "FileRead_StartUp --------------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr(FilePathNames::path_init);
			std::cout << iBuffer << std::endl;
	bool temp = iBuffer != nullptr;
	temp = true;
	ASSERT(iBuffer == nullptr);
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);

// get values from the Document;
	rapidjson::Value& s = d["ResX"];
	initialise._ResX = s.GetInt();
	s = d["ResY"];
	initialise._ResY = s.GetInt();
	s = d["Fullscreen"];
	initialise._Fullscreen = s.GetBool();
// cout for check
	std::cout << "Inital File Input" << std::endl
		<< "X:" << initialise._ResX << " Y:" << initialise._ResY << " Full = " << initialise._Fullscreen << std::endl
		<< "-------------------------------------" << std::endl;

	delete[] iBuffer;
}

/**
\brief Output to file a crash file with a message
*/
void FileOut_CrashLog(const char* msg) {
	std::fstream _file;
	_file.open(FilePathNames::path_crashLog, std::ios_base::out, std::ios_base::trunc);
	_file << "CRASH LOG" << std::endl
		<< msg << std::endl;
	_file.close();
}


// EXAMPLE FROM rapidJson.org
//// 1. Parse a JSON string into DOM.
//const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//rapidjson::Document d;
//d.Parse(json);
//// 2. Modify it by DOM.
//rapidjson::Value& s = d["stars"];
//s.SetInt(s.GetInt() + 1);
//// 3. Stringify the DOM
//rapidjson::StringBuffer buffer;
//rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//d.Accept(writer);
//// Output {"project":"rapidjson","stars":11}
//std::cout << buffer.GetString() << std::endl;
	// Using a reference for consecutive access is handy and faster.
//const Value& a = document["a"];
//assert(a.IsArray());
//for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
//	printf("a[%d] = %d\n", i, a[i].GetInt());
	// Below is for displaying error
//	d.Parse<rapidjson::kParseStopWhenDoneFlag>(src); // kParseStopWhenDoneFlag supresses the Parsing error
//	if (d.Parse(src).HasParseError()) { // this shows the parsing error
//		fprintf(stderr, "\nError(offset %u): %s\n",
//			(unsigned)d.GetErrorOffset(),
//			rapidjson::GetParseError_En(d.GetParseError()));

/******************************************************************************/
/**
\brief Read info for Player class
		Will get following values:
		- _HP_Player	// HP
		- _SPD_Player	// Speed
		- _FR_Player	// Fire rate
*/
/******************************************************************************/
//void FileRead_PlayerInfo() // Func to read initialization file
//{
//	//std::ifstream _file; // the input stream
//	//_file.open("player.txt", std::ios_base::in | std::ios_base::binary);
//	//if (!_file.is_open()) // file cannot be opened
//	//{
//	//	std::cout << "! WARNING !! Using default parameters!!!\n";
//	//	_HP_Player = _SPD_Player = _FR_Player = 0;
//	//}
//	//else // read info from file
//	//{
//	//	// 'global' varibles
//	//	int arrElement[MAX_ARR_SIZE] = { 0 };
//	//	std::string arrKey[MAX_ARR_SIZE];
//	//	int count = 0; // for use in storing elements into arrays
//
//	//	while (!_file.eof()) // while not eof
//	//	{
//	//		std::string line;
//	//		std::queue<int> queNum;
//	//		int pos = 0; // for substr position
//
//	//		getline(_file, line);
//	//		for (std::string::iterator itr = line.begin(); itr != line.end(); ++itr) {
//	//			// FIND mapKey
//	//			++pos; // find position of first non-alphabet, while counting cause need position
//	//			if (!AsciiLetterCheck(*itr))
//	//				arrKey[count] = line.substr(0, --pos);
//	//			// FIND mapElement
//	//			if (AsciiNumberCheck(*itr)) // only allow '.' and ASCII numbers
//	//				queNum.push(*itr);
//	//		}
//	//		// calc actual value stored in Queue
//	//		while (queNum.size()) {
//	//			int mult = MultTen(static_cast<int>(queNum.size())); // using MultTen to get the 1XXXX multiplier
//	//			int val = queNum.front() - 48; // -48 cause ASCII
//	//			queNum.pop();
//	//			val *= mult;
//	//			arrElement[count] += val;
//	//		}
//	//		++count;
//	//		pos = 0;
//	//	}
//
//	//	// cout all varibles
//	//	for (int i = 0; i < MAX_ARR_SIZE; ++i)
//	//		std::cout << arrKey[i] << " " << arrElement[i] << '\n';
//	//	std::cout << '\n';
//	//	// TODO save all data into a MAP
//	//}
//
//	//// cout windows settings for debug
//	//	//std::cout << "- DEBUG --       ResX = " << _ResX << "\n";
//	//	//std::cout << "- DEBUG --       ResY = " << _ResY << "\n";
//	//	//std::cout << "- DEBUG -- FullScreen = " << _Fullscreen<< "\n";
//
//	//	// proceed to call Windows_Init()
//	//	// OR
//	//	// exit function so Windows_Init can execute
//
//	return;
//}