#include "PrecompiledHeaders.h"
#include "PauseMenu.h"

void PauseMenu::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("P.NumOfObject") && document["P.NumOfObject"].IsInt())	//Checks if the variable exists in .Json file
		_numOfObject = document["H.MaxHealth"].GetInt();

	if (document.HasMember("P.ObjectID") && document["P.ObjectID"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["P.ObjectID"].Size(); i++)
		{
			if (document["P.ObjectID"][i].IsInt())
				_objectLinkID.push_back(document["P.ObjectID"][i].GetInt());
		}
}

void PauseMenu::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_numOfObject);
	prototypeDoc.AddMember("P.NumOfObject", value);

	value.SetArray();
	for (unsigned i = 0; i < _objectLinkID.size(); i++)
		value.PushBack(rapidjson::Value(_objectLinkID[i]).Move(), prototypeDoc.Allocator());

	prototypeDoc.AddMember("P.ObjectID", value);
}

void PauseMenu::Inspect()
{
	ImGui::Spacing();
	ImGui::InputInt("Num Of Objects ", &_numOfObject);
	ImGui::Spacing();

	int temp = _numOfObject - _objectLinkID.size();

	if (temp > 0)
		for (unsigned i = 0; i < temp; i++)
			_objectLinkID.push_back(0);
	else if (temp < 0)
		for (; temp < 0; temp++)
			_objectLinkID.pop_back();

	for (unsigned i = 0; i < _numOfObject; i++)
	{
		ImGui::Spacing();
		std::string temp = std::string{ "object ID " }  +std::to_string(i);
		ImGui::InputInt(temp.c_str(), &_objectLinkID[i]);
		ImGui::Spacing();
	}
}

PauseMenu::PauseMenu()
{
}

PauseMenu* PauseMenu::Clone()
{
	return new PauseMenu(*this);
}

void PauseMenu::Init()
{
	for (unsigned i = 0; i < _objectLinkID.size(); i++)
		_object.push_back(MyLinkFactory.GetLinkIDObject(_objectLinkID[i]));
}

void PauseMenu::Update(double dt)
{
}

void PauseMenu::EnablePauseMenu(bool t)
{
	for (unsigned i = 0; i < _object.size(); i++)
		_object[i]->SetEnable(t);
}
