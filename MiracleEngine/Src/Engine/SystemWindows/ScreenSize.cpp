#include "PrecompiledHeaders.h"
#include "ScreenSize.h"
#include "Tools/FileIO/Serialiser.h"



ScreenSize::ScreenSize() 
	: _ResX{ 0 }, _ResY{ 0 }, _Fullscreen{ false }
{}



void ScreenSize::FileRead_StartUp()
{
	std::cout << std::endl << "FileRead_StartUp --------------------" << std::endl;
	//rapidjson::Document d;
	//char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/Window/init.json");
	//std::cout << iBuffer << std::endl;
	//bool temp = iBuffer != nullptr;
	//temp = true;
	//ASSERT(iBuffer != nullptr);
	//d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);


	Serialiser document("./Resources/TextFiles/Window/init.json");

	// get values from the Document;
	rapidjson::Value& s = document["ResX"];
	_ResX = s.GetInt();
	s = document["ResY"];
	_ResY = s.GetInt();
	s = document["Fullscreen"];
	_Fullscreen = s.GetBool();
	// cout for check
	std::cout << "Inital File Input" << std::endl
		<< "X:" << _ResX << " Y:" << _ResY << " Full = " << _Fullscreen << std::endl
		<< "-------------------------------------" << std::endl << std::endl;
}



int ScreenSize::GetResX() const
{
	return _ResX;
}


int ScreenSize::GetResY() const
{
	return _ResY;
}