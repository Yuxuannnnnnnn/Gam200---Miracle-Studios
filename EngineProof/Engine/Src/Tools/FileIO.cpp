#include "FileIO.h"
#include <comdef.h> // For _bstr_t class, to convert const wchar_t* to const char*

#define MAX_CHAR_ARR_BUFFER 1000

namespace FilePathNames {
	const char* path_player = "./Resources/TextFiles/player.json";
	const char* path_init = "./Resources/TextFiles/init.json";
	const char* path_outTest = "./Resources/TextFiles/test.txt";
	const char* path_crashLog = "./Resources/TextFiles/crashlog.txt";
	const char* path_level = "./Resources/TextFiles/TestLevel.txt";
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
	ASSERT(typeid(store).name() == typeid(bool).name())
		store = static_cast<bool>(val.GetBool());
}
void JsonDynamicStore(float& store, rapidjson::Value& val)
{
	ASSERT(typeid(store).name() == typeid(float).name())
		store = static_cast<float>(val.GetFloat());
}
void JsonDynamicStore(int& store, rapidjson::Value& val)
{
	ASSERT(typeid(store).name() == typeid(int).name())
		store = static_cast<int>(val.GetInt());
}
void JsonDynamicStore(std::vector<int> &store, rapidjson::Value& val)
{
	ASSERT(val.IsArray()) // check to ensure that the 'val' is also an array
		for (unsigned i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetInt());
}
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val)
{
	ASSERT(val.IsArray())
		for (unsigned i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetFloat());
}
void JsonDynamicStore(Vector3& store, rapidjson::Value& val)
{
	ASSERT(val.IsArray())
	Vector3 tempVec(val[0].GetFloat(), val[1].GetFloat(), 1);
	store = tempVec;
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
	ASSERT(iBuffer != nullptr);
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
void FileOut_CrashLog(_In_z_ wchar_t const* _Message,
	_In_z_ wchar_t const* _File,
	_In_   unsigned       _Line) {

	//conversion of wchar_t const * to const char *
	_bstr_t a(_Message);
	const char* message = a;

	//conversion of wchar_t const * to const char *
	_bstr_t b(_File);
	const char* file = b;

	std::fstream _file;
	//std::ios_base::trunc forces the file to be created
	_file.open(FilePathNames::path_crashLog, std::ios_base::out, std::ios_base::trunc);
	_file << "CRASH LOG" << std::endl << "ASSERT FAILED: " << message << " @ " << file << " (" << _Line << ")" << std::endl;
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