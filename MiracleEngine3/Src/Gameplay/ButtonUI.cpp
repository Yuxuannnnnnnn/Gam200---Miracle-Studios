#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

ButtonUI::ButtonUI() :
	_buttonType{ (int)ButtonType::PLAY }
{
}

void ButtonUI::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_buttonType = (document["ButtonType"].IsInt());
	}
}

void ButtonUI::OnMouseDown()
{
	switch (_buttonType)
	{
	case (int)ButtonType::PLAY:
		EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::LEVEL1);
		break;
	case (int)ButtonType::QUIT:
		EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::QUIT);
		break;
	case (int)ButtonType::INSTRUCTION:
		EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::INSTRUCTION);
		break;
	case (int)ButtonType::MENU:
		EngineSystems::GetInstance()._sceneManager->ChangeScene(Scenes::MAIN_MENU);
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

void ButtonUI::Update()
{

}

