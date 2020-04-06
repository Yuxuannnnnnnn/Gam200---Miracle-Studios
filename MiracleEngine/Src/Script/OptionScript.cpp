#include "PrecompiledHeaders.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"

OptionScript::OptionScript() :
	_currFullscreen{ false }, _newFullscreen{ false },
	_currMasterSound{ 0.f }, _newMasterSound{ 0.f },
	_currMusic{ 0.f }, _newMusic{ 0.f }, _adjustedMusic{ 0.f },
	_currSFX{ 0.f }, _newSFX{ 0.f }, _adjustedSFX{ 0.f }
{
}













void OptionScript::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_buttonType = (document["ButtonType"].IsInt());
	}
}

void OptionScript : :DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_buttonType);
	prototypeDoc.AddMember("ButtonType", value);
	value.Clear();
}

void OptionScript::OnMouseDown()
{
	switch (_buttonType)
	{
	case (int)ButtonType::NONE:
		break;
	case (int)ButtonType::PLAY:
		EngineSystems::GetInstance()._sceneManager->ChangeScene("Level1");
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

void OptionScript::OnMouseEnter()
{
	;
}
void OptionScript::OnMouseOver()
{
	;
}
void OptionScript::OnMouseExit()
{
	;
}

void OptionScript::Update()
{

}

