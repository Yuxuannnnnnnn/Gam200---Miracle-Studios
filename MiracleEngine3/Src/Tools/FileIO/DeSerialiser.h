#pragma once
#include "JsonHeader.h"


class DeSerialiser
{
	rapidjson::Document _level;
	rapidjson::MemoryPoolAllocator<>& _allocator;

	std::string _filename;

public:

	DeSerialiser(std::string filename)
		:_level{}, _allocator{ _level.GetAllocator() }, _filename{filename}
	{
		_level.SetObject();	//Set the document as an OverArching Object
	}


	//Value b(true);    // calls Value(bool)
	//Value i(-123);    // calls Value(int)
	//Value u(123u);    // calls Value(unsigned)
	//Value d(1.5);     // calls Value(double)
	//Value o(kObjectType);

	//Value a(kArrayType);
	//// a.PushBack(Value(42), allocator);       // will not compile
	//a.PushBack(Value().SetInt(42), allocator); // fluent API
	//a.PushBack(Value(42).Move(), allocator);   // same as above

	//Value author;
	//char buffer[10];
	//int len = sprintf(buffer, "%s %s", "Milo", "Yip"); // dynamically created string.
	//author.SetString(buffer, len, document.GetAllocator());

	//s.SetString("rapidjson");    // can contain null character, length derived at compile time
	//s = "rapidjson";             // shortcut, same as above

	//const char* cstr = getenv("USER");
	//size_t cstr_len = ...;                 // in case length is available
	//Value s;
	//// s.SetString(cstr);                  // will not compile
	//s.SetString(StringRef(cstr));          // ok, assume safe lifetime, null-terminated
	//s = StringRef(cstr);                   // shortcut, same as above
	//s.SetString(StringRef(cstr, cstr_len)); // faster, can contain null character
	//s = StringRef(cstr, cstr_len);          // shortcut, same as abov

	void AddMember(const std::string& key, rapidjson::Value& value)
	{
		rapidjson::Value name(key.c_str(), _allocator);

		_level.AddMember(name, value, _allocator);
	}


	rapidjson::MemoryPoolAllocator<>& Allocator()
	{
		return _allocator;
	}



	~DeSerialiser()
	{
		rapidjson::StringBuffer buf;							//buffer -  to output from the Json Document	
		rapidjson::Writer<rapidjson::StringBuffer> writer(buf);	//Writer handler - that contains the stringbuffer
		_level.Accept(writer);									//Output as json text into stringbuffer via Writer

		std::string json(buf.GetString(), buf.GetSize());		//convert stringbuffer to std::string


		std::ofstream file(_filename.c_str()); //open a file with the param name
		file << json;							//Write std::string type into the file

		if (!file.good())	//Check whether state of stream is good 
			throw std::runtime_error("Can't write the JSON string to the file!");
	}
};
