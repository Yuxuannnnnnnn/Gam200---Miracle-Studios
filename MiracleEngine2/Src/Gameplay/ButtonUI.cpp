#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"


ButtonUI::ButtonUI() :
	_buttonType{ (int)ButtonType::NONE }
{
}

void ButtonUI::Update()
{

}

void ButtonUI::SerialiseComponent(Serialiser& document)
{
	
}