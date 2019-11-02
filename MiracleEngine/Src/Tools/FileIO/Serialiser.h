#pragma once

#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying

#ifndef SERIALISER_H
#define SERIALISER_H

#define MAX_CHAR_ARR_BUFFER 1000

class Serialiser
{
private:
	rapidjson::Document _document;
	char* iBuffer;

public:
	Serialiser(std::string file);
	~Serialiser();

	bool HasMember(const char* string);

	rapidjson::Value& operator[] (const char* string);


	// take in power, x10 by power amt
	int MultTen(int power);
	bool AsciiLetterCheck(const char c);
	bool AsciiNumberCheck(const char c);
	int AsciiNumberCovert(const char c);

	/**
	\brief Function to use to allow parsing of all relevant json elements
	*/
	bool JsonParseChecker(const char c);
	char* FileRead_FileToCharPtr(const char* FileName);

};

#endif

