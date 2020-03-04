#include "PrecompiledHeaders.h"
#include "PauseMenu.h"

void PauseMenu::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("P.NumOfObject") && document["P.NumOfObject"].IsInt())	//Checks if the variable exists in .Json file
		_numOfObject = document["P.NumOfObject"].GetInt();

	if (document.HasMember("P.ObjectID") && document["P.ObjectID"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["P.ObjectID"].Size(); i++)
		{
			if (document["P.ObjectID"][i].IsInt())
				_objectLinkID.push_back(document["P.ObjectID"][i].GetInt());
		}
}

//Function Not needed for scripts
void PauseMenu::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetInt(_numOfObject);
	//prototypeDoc.AddMember("P.NumOfObject", value);
	//
	//value.SetArray();
	//for (unsigned i = 0; i < _objectLinkID.size(); i++)
	//	value.PushBack(rapidjson::Value(_objectLinkID[i]).Move(), prototypeDoc.Allocator());
	//
	//prototypeDoc.AddMember("P.ObjectID", value);
}

void PauseMenu::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetInt(_numOfObject);
	prototypeDoc.AddMember("P.NumOfObject", value, allocator);

	value.SetArray();
	for (unsigned i = 0; i < _objectLinkID.size(); i++)
		value.PushBack(rapidjson::Value(_objectLinkID[i]).Move(), allocator);

	prototypeDoc.AddMember("P.ObjectID", value, allocator);
}

void PauseMenu::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	size_t UId = protoLogicCom->GetScriptContianer()[_type];

	PauseMenu* script = (PauseMenu*)(MyLogicSystem.getScriptPtr(UId));

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value NumOfObject;
	rapidjson::Value ObjectID;

	bool addComponentIntoSceneFile = false;

	if (script->_numOfObject != _numOfObject)
	{
		addComponentIntoSceneFile = true;
		NumOfObject.SetInt(_numOfObject);
	}

	addComponentIntoSceneFile = true;
	ObjectID.SetArray();
	for (unsigned i = 0; i < _objectLinkID.size(); i++)
		ObjectID.PushBack(rapidjson::Value(_objectLinkID[i]).Move(), allocator);


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!NumOfObject.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("P.NumOfObject", NumOfObject, allocator);
		}

		if (!ObjectID.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("P.ObjectID", ObjectID, allocator);
		}
	}
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

PauseMenu::PauseMenu() : _init{false}
{
}

PauseMenu::~PauseMenu()
{
	MyInputSystem._pause = false;
}

PauseMenu* PauseMenu::Clone()
{
	return new PauseMenu(*this);
}

void PauseMenu::Init()
{
	_object.clear();

	MyFactory.SaveNewLinkID(1275, GetParentId());

	for (unsigned i = 0; i < _objectLinkID.size(); i++)
		_object.push_back(MyFactory.GetLinkIDObject(_objectLinkID[i]));

	for (unsigned i = 0; i < _object.size(); i++)
		_object[i]->SetEnable(false);
}

void PauseMenu::Update(double dt)
{
	if (!_init)
	{
		Init();
		_init = true;
	}
}

void PauseMenu::EnablePauseMenu(bool t)
{
	for (unsigned i = 0; i < _object.size(); i++)
		_object[i]->SetEnable(t);

	MyInputSystem._pause = t;
}
