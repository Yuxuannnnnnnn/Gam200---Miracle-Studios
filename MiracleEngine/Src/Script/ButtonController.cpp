#include "PrecompiledHeaders.h"
#include "ButtonController.h"

void ButtonController::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("B.SceneTag") && document["B.SceneTag"].IsInt())	//Checks if the variable exists in .Json file
		_currScene = document["B.SceneTag"].GetInt();
}

void ButtonController::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_currScene);
	prototypeDoc.AddMember("B.SceneTag", value);
	value.Clear();
}

void ButtonController::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Current Scene ID ", &_currScene);
	ImGui::Spacing();

	//ImGui::Spacing();
	//{
	//	ImGui::Spacing();

	//	static auto& TagList = MyPhysicsSystem._collisionTable.GetTagList();
	//	std::vector<const char*> list;
	//	list.push_back("Choose a Collider Tag ");
	//	static const char* name = list[0];


	//	int i = 1;
	//	static int select = 0;
	//	for (auto TagPair = TagList.begin(); TagPair != TagList.end(); TagPair++, i++)
	//	{
	//		const char* ptr = TagPair->first.c_str();
	//		list.push_back(ptr);
	//		if (TagPair->second == (size_t)_tag)
	//			select = i;
	//	}

	//	if (ImGui::BeginCombo(" ", list[select], 0)) // The second parameter is the label previewed before opening the combo.
	//	{
	//		for (int n = 0; n < list.size(); n++)
	//		{
	//			bool is_selected = (name == list[n]);
	//			if (ImGui::Selectable(list[n], is_selected))
	//			{
	//				_tag = TagList[list[n]];
	//				select = n;
	//			}

	//		}
	//		ImGui::EndCombo();
	//	}
	//}
}

ButtonController::ButtonController() :
	_currScene{0}
{
}

ButtonController* ButtonController::Clone()
{
	return new ButtonController{*this};
}

void ButtonController::Init()
{
}

void ButtonController::Update(double dt)
{
	(void)dt;

	if (!_input->KeyRelease(MOUSE_LBUTTON))
		return;

	switch (_currScene)
	{
	case (int)SceneTag::MAINMENU:
	{
		if (_input->ButtonTrigger(10)) // start
		{
			MyFactory.ChangeScene("Level1");
			break;
		}
		//if (_input->ButtonTrigger(11)) // options
		//	MyFactory.ChangeScene("Level1");
		//if (_input->ButtonTrigger(12)) // instructions
		//	MyFactory.ChangeScene("Level1");
		//if (_input->ButtonTrigger(13)) // leaderboard
		//	MyFactory.ChangeScene("Level1");
		//if (_input->ButtonTrigger(14)) // help
		//	MyFactory.ChangeScene("Level1");
		//if (_input->ButtonTrigger(15)) // credits
		//	MyFactory.ChangeScene("Level1");
		if (_input->ButtonTrigger(16)) // quit
		{
			MyFactory.ChangeScene("Quit");
			break;
		}
	}
	default:
		break;
	}

}
