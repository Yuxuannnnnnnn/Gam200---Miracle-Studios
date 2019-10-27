#include "PrecompiledHeaders.h"
#include "ScreenSize.h"


void ScreenSize::FileRead_StartUp()
{
	std::cout << std::endl << "FileRead_StartUp --------------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/init.json");
	std::cout << iBuffer << std::endl;
	bool temp = iBuffer != nullptr;
	temp = true;
	ASSERT(iBuffer != nullptr);
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);

	// get values from the Document;
	rapidjson::Value& s = d["ResX"];
	_ResX = s.GetInt();
	s = d["ResY"];
	_ResY = s.GetInt();
	s = d["Fullscreen"];
	_Fullscreen = s.GetBool();
	// cout for check
	std::cout << "Inital File Input" << std::endl
		<< "X:" << _ResX << " Y:" << _ResY << " Full = " << _Fullscreen << std::endl
		<< "-------------------------------------" << std::endl << std::endl;

	delete[] iBuffer;
}