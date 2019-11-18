
#include "PrecompiledHeaders.h"
#include "FontComponent.h"



void FontComponent::SerialiseComponent(Serialiser& document)
{

	if (document.HasMember("FontId") && document["FontId"].IsInt())	//Checks if the variable exists in .Json file
	{
		_fontID = (document["FontId"].GetInt());
	}
}

void FontComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_fontID);
	prototypeDoc.AddMember("FontId", value);
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

}