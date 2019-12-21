#include "PrecompiledHeaders.h"
#include "Serialiser.h"



//convert file into rapidJson Document format
Serialiser::Serialiser(std::string file)
	:iBuffer{nullptr}
{
	iBuffer = FileRead_FileToCharPtr(file.c_str()); //Convert file into a char* buffer
	//std::cout << iBuffer << std::endl;
	ASSERT(iBuffer != nullptr);								//Check if ibuffer contains a string
	_document.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);	//Convert char* buffer into rapidJson Document format
}

Serialiser::~Serialiser()
{
	delete []iBuffer;
}

bool Serialiser::HasMember(const char* string)
{
	return _document.HasMember(string);
}

rapidjson::Value& Serialiser::operator[](const char* string)
{
	return _document[string];

}

int Serialiser::MultTen(int power)
{
	int val = 1;
	while (--power)
		val *= 10;
	return val;
}

bool Serialiser::AsciiLetterCheck(const char c)
{
	// 'A'&'Z' || 'a'&'z'
	return (c > 64 && c < 91 || c > 96 && c < 123) ? true : false;
}

bool Serialiser::AsciiNumberCheck(const char c)
{
	return (c > 47 && c < 58) ? true : false; // 0 to 9
}

int Serialiser::AsciiNumberCovert(const char c)
{
	// -48 cause ASCII
	return c - 48;
}

bool Serialiser::JsonParseChecker(const char c)
{
	if (AsciiNumberCheck(c) ||
		AsciiLetterCheck(c) ||
		c == '/' || c == '\\' ||
		c == '\"' || c == ',' ||
		c == ':' || c == '.' ||
		c == '{' || c == '}' ||
		c == '[' || c == ']' || c =='-'
		)
		return true;
	return false;
}

char* Serialiser::FileRead_FileToCharPtr(const char* FileName)
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