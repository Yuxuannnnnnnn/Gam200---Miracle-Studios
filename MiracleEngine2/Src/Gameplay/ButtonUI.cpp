#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void ButtonUI::OnMouseDown()
{
	switch (_buttonType)
	{
	case (int)ButtonType::NONE:
		break;
	case (int)ButtonType::PLAY:
		EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::LEVEL1);
		break;
	case (int)ButtonType::PAUSE:

		break;
	case (int)ButtonType::QUIT:

		break;
	case (int)ButtonType::MENU:

		break;
	case (int)ButtonType::RESTART:

		break;
	default:
		break;
	}
}

void ButtonUI::OnMouseEnter()
{
	;
}
void ButtonUI::OnMouseOver()
{
	;
}
void ButtonUI::OnMouseExit()
{
	;
}

ButtonUI::ButtonUI() :
	_buttonType{ (int)ButtonType::PLAY }
{
}

void ButtonUI::Update()
{

}

void ButtonUI::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_buttonType = (document["ButtonType"].IsInt());
	}
}