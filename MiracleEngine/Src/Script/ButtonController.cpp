#include "PrecompiledHeaders.h"
#include "ButtonController.h"
#include "PauseMenu.h"
#include "Script/LoadingScreen.h"

void ButtonController::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("B.SceneTag") && document["B.SceneTag"].IsInt())	//Checks if the variable exists in .Json file
		_currScene = document["B.SceneTag"].GetInt();

	if (document.HasMember("B.LoadingLinkId") && document["B.LoadingLinkId"].IsInt())	//Checks if the variable exists in .Json file
		_loadingLinkId = document["B.LoadingLinkId"].GetInt();
}

void ButtonController::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetInt(_currScene);
	//prototypeDoc.AddMember("B.SceneTag", value);
}

//For nonclonables Or Prototypes
void ButtonController::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_currScene);
	prototypeDoc.AddMember("B.SceneTag", value, allocator);

	value.SetInt(_loadingLinkId);
	prototypeDoc.AddMember("B.LoadingLinkId", value, allocator);

}

void ButtonController::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	ButtonController* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), ButtonController);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value currScene;
	rapidjson::Value LoadingLinkId;

	bool addComponentIntoSceneFile = false;

	if (script->_currScene != _currScene)
	{
		addComponentIntoSceneFile = true;
		currScene.SetInt(_currScene);
	}

	if (script->_loadingLinkId != _loadingLinkId)
	{
		addComponentIntoSceneFile = true;
		LoadingLinkId.SetInt(_loadingLinkId);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!currScene.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("B.SceneTag", currScene, allocator);
		}

		if (!LoadingLinkId.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("B.LoadingLinkId", LoadingLinkId, allocator);
		}

	}

}



void ButtonController::Inspect()
{
	//ImGui::Spacing();
	//ImGui::InputInt("Current Scene ID ", &_currScene);
	//ImGui::Spacing();
}

ButtonController::ButtonController() :
	_currScene{ 0 }, _pauseMenu{ nullptr }, _loadingLinkId{0}
{
}

ButtonController* ButtonController::Clone()
{
	return new ButtonController{*this};
}

void ButtonController::Init()
{
	if (_currScene == 2)
		_pauseMenu = GetScriptByLogicComponent(GetComponentObject( GetLinkObject(1275), Logic), PauseMenu);

	if (_currScene == 1)
		_LoadingObj = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(_loadingLinkId), Logic), LoadingScreen);
}

void ButtonController::LoadResource()
{

}

void ButtonController::Update(double dt)
{
	if (_currScene == 2)
	{
		if (_input->ButtonTrigger(60))
			((PauseMenu*)_pauseMenu)->EnablePauseMenu(false);
		else if (_input->ButtonTrigger(30)) // return to menu
			MyFactory.ChangeScene("MainMenu");
	}

	if (dt < 0)
		return;

	if (_currScene == 1)
	{
		if (_input->ButtonTrigger(10)) // start
			((LoadingScreen*)_LoadingObj)->StartLoading("truelevel1");
		else if (_input->ButtonTrigger(11)) // options
			MyFactory.ChangeScene("OptionPage");
		else if (_input->ButtonTrigger(12)) // instructions
			MyFactory.ChangeScene("instructionPage");
		else if (_input->ButtonTrigger(13)) // leaderboard
			MyFactory.ChangeScene("LeaderBoardPage");
		else if (_input->ButtonTrigger(15)) // credits
			MyFactory.ChangeScene("CreditPage");
		else if (_input->ButtonTrigger(16)) // quit
			MyFactory.ChangeScene("Quit");
	}
	else if (_currScene == 3 && _input->ButtonTrigger(30))
		MyFactory.ChangeScene("MainMenu");
	
}
