#include "PrecompiledHeaders.h"
#include "EntrancePortal.h"
#include "Player.h"
void EntrancePortal::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("E.OpenEntranceFileName") && document["E.OpenEntranceFileName"].IsString())
		_openPortalFileName = document["E.OpenEntranceFileName"].GetString();

	if (document.HasMember("E.CloseEntranceFileName") && document["E.CloseEntranceFileName"].IsString())
		_closePortalFileName = document["E.CloseEntranceFileName"].GetString();

	if (document.HasMember("E.ProgressCount") && document["E.ProgressCount"].IsInt())
		_progressCount = document["E.ProgressCount"].GetInt();

	if (document.HasMember("E.NextScene") && document["E.NextScene"].IsString())
		_nextScene = document["E.NextScene"].GetString();

	
}

//No need this function
void EntrancePortal::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	//rapidjson::Value value;
	//
	//value.SetString(rapidjson::StringRef(_openPortalFileName.c_str()));
	//prototypeDoc.AddMember("E.OpenEntranceFileName", value);
	//
	//value.SetString(rapidjson::StringRef(_closePortalFileName.c_str()));
	//prototypeDoc.AddMember("E.CloseEntranceFileName", value);
	//
	//value.SetString(rapidjson::StringRef(_nextScene.c_str()));
	//prototypeDoc.AddMember("E.NextScene", value);
	//
	//value.SetInt(_progressCount);
	//prototypeDoc.AddMember("E.ProgressCount", value);
}

void EntrancePortal::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(ToScriptName(_type)));
	prototypeDoc.AddMember("Script2Id", value, allocator);

	value.SetString(rapidjson::StringRef(_openPortalFileName.c_str()));
	prototypeDoc.AddMember("E.OpenEntranceFileName", value, allocator);

	value.SetString(rapidjson::StringRef(_closePortalFileName.c_str()));
	prototypeDoc.AddMember("E.CloseEntranceFileName", value, allocator);

	value.SetInt(_progressCount);
	prototypeDoc.AddMember("E.ProgressCount", value, allocator);

	value.SetString(rapidjson::StringRef(_nextScene.c_str()));
	prototypeDoc.AddMember("E.NextScene", value, allocator);
}

void EntrancePortal::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	EntrancePortal* script = GetScriptByLogicComponent(dynamic_cast<LogicComponent*>(protoCom), EntrancePortal);

	if (!script)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value OpenEntranceFileName;
	rapidjson::Value CloseEntranceFileName;
	rapidjson::Value ProgressCount;
	rapidjson::Value NextScene;

	bool addComponentIntoSceneFile = false;

	if (script->_openPortalFileName.compare(_openPortalFileName))
	{
		addComponentIntoSceneFile = true;
		OpenEntranceFileName.SetString(rapidjson::StringRef(_openPortalFileName.c_str()));
	}

	if (script->_closePortalFileName.compare(_closePortalFileName))
	{
		addComponentIntoSceneFile = true;
		CloseEntranceFileName.SetString(rapidjson::StringRef(_closePortalFileName.c_str()));
	}

	if (script->_progressCount != _progressCount)
	{
		addComponentIntoSceneFile = true;
		ProgressCount.SetInt(_progressCount);
	}

	if (script->_nextScene.compare(_nextScene))
	{
		addComponentIntoSceneFile = true;
		NextScene.SetString(rapidjson::StringRef(_nextScene.c_str()));
	}



	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		rapidjson::Value scriptName;

		scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
		value.AddMember("Script2Id", scriptName, allocator);


		if (!OpenEntranceFileName.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("E.OpenEntranceFileName", OpenEntranceFileName, allocator);
		}

		if (!CloseEntranceFileName.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("E.CloseEntranceFileName", CloseEntranceFileName, allocator);
		}

		if (!ProgressCount.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("E.ProgressCount", ProgressCount, allocator);
		}

		if (!NextScene.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("E.NextScene", NextScene, allocator);
		}
	}
}

void EntrancePortal::Inspect()
{
	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());

	int i = 0;
	int select1 = 0;
	int select2 = 0;

	for (auto& graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();
		list[i] = ptr;

		if (!strncmp(ptr, _openPortalFileName.c_str(), 20))
			select1 = i;

		if (!strncmp(ptr, _closePortalFileName.c_str(), 20))
			select2 = i;

		i++;
	}

	static ComboFilterState s1 = { select1, 0 };
	static char buf1[128];
	static ImGuiFunctions function;
	static bool op = false;
	static bool* open = &op;

	if (_openPortalFileName.empty())
		strncpy(buf1, "type text here...", 18);
	else
		strncpy(buf1, _openPortalFileName.c_str(), _openPortalFileName.size());

	function.ComboFilter("Open Portal Texture", buf1, IM_ARRAYSIZE(buf1), list, (int)list.size(), s1, _openPortalFileName, open);
	ImGui::Spacing();

	static ComboFilterState s2 = { select2, 0 };
	static char buf2[128];

	if (_closePortalFileName.empty())
		strncpy(buf2, "type text here...", 18);
	else
		strncpy(buf2, _closePortalFileName.c_str(), _closePortalFileName.size());

	function.ComboFilter("Closed Portal Texture", buf2, IM_ARRAYSIZE(buf2), list, (int)list.size(), s2, _closePortalFileName, open);
	ImGui::Spacing();


	ImGui::Spacing();
	ImGui::InputInt("Max Progression Count ", &_progressCount);
	ImGui::Spacing();


	ImGui::Spacing();
	std::string string = std::string("Next Level :");
	//strncpy(_current_ObjectType, _ObjectType.c_str(), _ObjectType.length());


	char scene[100] = "\0";
	strncpy(scene, _nextScene.c_str(), _nextScene.length());
	ImGui::InputText(string.c_str(), scene, 100);
	_nextScene = scene;
	ImGui::Spacing();
}

EntrancePortal::EntrancePortal() :
	_playerScript{ nullptr },
	_graphicComponent{ nullptr },
	_progressCount{0},
	_clear{false}
{
}

EntrancePortal* EntrancePortal::Clone()
{
	return new EntrancePortal(*this);
}

void EntrancePortal::Init()
{
	_graphicComponent = (GraphicComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Graphic);
	_graphicComponent->SetFileName(_closePortalFileName);

	GameObject* tempPlayer = MyFactory.GetLinkIDObject(999);
	std::string temp = "Player";
	_playerScript = MyLogicSystem.GetScriptList()[((LogicComponent*)(tempPlayer->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]];
	_player = (TransformComponent*)(tempPlayer->GetComponent(ComponentId::CT_Transform));

	_popUp = MyFactory.GetLinkIDObject(9542);
	_popUpPos = (TransformComponent*)_popUp->GetComponent(ComponentId::CT_Transform);
}

void EntrancePortal::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ _closePortalFileName, MyResourceSystem.GetTexture2DResourcePath(_closePortalFileName) });
	MyResourceManager.AddNewTexture2DResource({ _openPortalFileName, MyResourceSystem.GetTexture2DResourcePath(_openPortalFileName) });
#endif
}

void EntrancePortal::Update(double dt)
{
	if (dt < 0)
		return;

	if (!_clear)
	{
		if (_KillCount >= _progressCount)
			OpenPortal();
	}
	else
		_popUpPos->SetPos(Vec3{ _player->GetPos()._x, _player->GetPos()._y + 300, 1.f});
}

void EntrancePortal::OpenPortal()
{
	_clear = true;
	_graphicComponent->SetFileName(_openPortalFileName);
	_popUp->SetEnable(true);
}

void EntrancePortal::OnTrigger2DEnter(Collider2D* other)
{
	if (_clear)
	{
		std::string otherType = ((IdentityComponent*)other->GetParentPtr()->GetComponent(ComponentId::CT_Identity))->ObjectType();

		if (!otherType.compare("player"))
			MyFactory.ChangeScene(_nextScene);
	}
}

void EntrancePortal::IncreaseKillCount(int kills)
{
	_KillCount += kills;
}
