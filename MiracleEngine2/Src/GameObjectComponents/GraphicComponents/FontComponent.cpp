
#include "PrecompiledHeaders.h"
#include "FontComponent.h"



void FontComponent::SerialiseComponent(Serialiser& document)
{

	if (document.HasMember("FontId") && document["FontId"].IsInt())	//Checks if the variable exists in .Json file
	{
		_fontID = (document["FontId"].GetInt());
	}

	if (document.HasMember("FontString") && document["FontString"].IsString())	//Checks if the variable exists in .Json file
	{
		_fontString = (document["FontString"].GetString());
	}
}

void FontComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_fontID);
	prototypeDoc.AddMember("FontId", value);

	value.SetString(rapidjson::StringRef(_fontString.c_str()));
	prototypeDoc.AddMember("FontString", value);
}


void FontComponent::SetFontID(int num)
{
	_fontID = num;
}



std::string FontComponent::ComponentName() const
{
	return "Font Component";
}

std::string& FontComponent::GetFontString()
{
	return _fontString;
}

void FontComponent::Inspect()
{
	char* string = new char[300];
	ImGui::InputText("Text To OutPut  ", string, 300);
	_fontString = string;
	delete []string;
}