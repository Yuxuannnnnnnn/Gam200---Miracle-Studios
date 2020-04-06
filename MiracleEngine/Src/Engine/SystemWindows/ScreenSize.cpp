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


	if (document.HasMember("currFullscreen") && document["currFullscreen"].IsBool())	//Checks if the variable exists in .Json file
	{
		_Fullscreen = (document["currFullscreen"].GetBool());
	}


	if (document.HasMember("currResolution") && document["currResolution"].IsArray())	//Checks if the variable exists in .Json file
	{
		_ResX = document["currResolution"][0].GetFloat();
		_ResY = document["currResolution"][1].GetFloat();
	}


	if (document.HasMember("currMasterSound") && document["currMasterSound"].IsFloat())	//Checks if the variable exists in .Json file
	{
		 MyAudioSystem.SetMasterVolume((document["currMasterSound"].GetFloat()));
	}
	
	if (document.HasMember("currMusic") && document["currMusic"].IsFloat())	//Checks if the variable exists in .Json file
	{
		MyAudioSystem.SetBGMVolume((document["currMusic"].GetFloat()));
	}
	
	if (document.HasMember("currSFX") && document["currSFX"].IsFloat())	//Checks if the variable exists in .Json file
	{
		MyAudioSystem.SetSFXVolume((document["currSFX"].GetFloat()));
	}



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