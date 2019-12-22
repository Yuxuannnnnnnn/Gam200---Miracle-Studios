#pragma once
#include "PrecompiledHeaders.h"
#include "FileIO.h"


//#define MAX_CHAR_ARR_BUFFER 1000

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
bool JsonParseChecker(const char c)
{
	if (AsciiNumberCheck(c) ||
		AsciiLetterCheck(c) ||
		c == '\"' || c == ',' || c == ':'|| c == '.' ||
		c == '{' || c == '}' ||	c == '[' || c == ']' ||
		c == '_' 
		)
		return true;
	return false;
}

/**
\brief Functions to make allow use of single func to allow different input type
	originally did as template, but kept getting warning of info loss on conversion of int/float to typeT
	error when having doing vector
*/

void JsonDynamicStore(bool& store, rapidjson::Value &val)
{
	ASSERT(val.IsBool())
		store = static_cast<bool>(val.GetBool());
	return;
}
void JsonDynamicStore(float& store, rapidjson::Value& val)
{
	ASSERT(val.IsFloat())
		store = static_cast<float>(val.GetFloat());
}
void JsonDynamicStore(int& store, rapidjson::Value& val)
{
	ASSERT(val.IsInt())
		store = static_cast<int>(val.GetInt());
}
void JsonDynamicStore(unsigned int& store, rapidjson::Value& val)
{
	ASSERT(val.IsUint())
		store = static_cast<unsigned int>(val.GetUint());
}
void JsonDynamicStore(std::vector<int> &store, rapidjson::Value& val)
{
	ASSERT(val.IsArray()) // check to ensure that the 'val' is also an array
		for (unsigned int i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetInt());
	return;
}
void JsonDynamicStore(std::vector<float>& store, rapidjson::Value& val)
{
	ASSERT(val.IsArray())
		for (unsigned int i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetFloat());
	return;
}
void JsonDynamicStore(std::vector<unsigned int>& store, rapidjson::Value& val)
{
	ASSERT(val.IsArray())
		for (unsigned int i = 0; i < val.Size(); ++i)
			store.push_back(val[i].GetInt());
	return;
}
void JsonDynamicStore(Vector3& store, rapidjson::Value& val)
{
	//Vector3 tempVec(val[0].GetFloat(), val[1].GetFloat(), 1);
	ASSERT(val.IsArray())
	{
		store.SetX(val[0].GetFloat());
		store.SetY(val[1].GetFloat());
		store.SetZ(1);
	}
	return;
}
void JsonDynamicStore(std::string& store, rapidjson::Value& val)
{
	ASSERT(val.IsString())
	{
		store.clear();
		store = val.GetString();
	}
	return;
}
//void JsonDynamicStore(TransformComponent* store, rapidjson::Value& val, ComponentTypes type)
//{
//	if (val.IsArray())
//	{
//		Vector3 tempVec(val[0].GetFloat(), val[1].GetFloat(), 1);
//		if (type == TRANSFORMSUBCOMPONENT_POS)
//			store->SetPos(tempVec);
//		else if (type == TRANSFORMSUBCOMPONENT_SCALE)
//			store->SetScale(tempVec);
//		else
//			std::cout << "JsonDynamicStore - TransformComponent Array Error\n";
//	}
//	else // type == TRANSFORMSUBCOMP_ROTATE
//		store->SetRotate(val.GetFloat());
//	return;
//}

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
			if (JsonParseChecker(c))
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
\brief Function to make file input into std::vector<string>
*/
std::vector<std::string> FileRead_FileToStringVector(const char* FileName)
{
	std::vector<std::string> stringVec;
	char* strType = new char[20];
	// open file
	std::fstream _file;
	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
	if (!_file.is_open())
	{
		std::cout << "! WARNING !! File Cannot Open!!!\n";
		return stringVec;
	}
	while (_file.good())
	{
		//_file >> strType;
		//stringVec.push_back(_file.getline());
	}
	_file.close();
	return stringVec;
}

/**
\brief Output to file a crash file with a message, // TODO : Move to DebugSys
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
	_file.open("./Resources/TextFiles/Debug/crashlog.txt", std::ios_base::out, std::ios_base::trunc);
	_file << "CRASH LOG" << std::endl << "ASSERT FAILED: " << message << " @ " << file << " (" << _Line << ")" << std::endl;
	_file.close();
}


