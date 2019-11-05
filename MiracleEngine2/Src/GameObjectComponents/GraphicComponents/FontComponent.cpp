
#include "PrecompiledHeaders.h"
#include "FontComponent.h"



void FontComponent::SerialiseComponent(Serialiser& document)
{

	if (document.HasMember("FontId") && document["FontId"].IsInt())	//Checks if the variable exists in .Json file
	{
		_fontID = (document["FontId"].GetInt());
	}
}
