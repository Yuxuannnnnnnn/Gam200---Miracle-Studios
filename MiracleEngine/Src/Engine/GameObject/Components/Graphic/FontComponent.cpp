
#include "PrecompiledHeaders.h"
#include "FontComponent.h"



void FontComponent::SerialiseComponent(Serialiser& document)
{



	if (document.HasMember("FontString") && document["FontString"].IsString())	//Checks if the variable exists in .Json file
	{
		_fontString = (document["FontString"].GetString());
	}
}

void FontComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;


	value.SetString(rapidjson::StringRef(_fontString.c_str()));
	prototypeDoc.AddMember("FontString", value);
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
	static char buffer[300] = " ";
	ImGui::InputText("Text To OutPut  ", buffer, 300);
	_fontString = buffer;
}