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

void EntrancePortal::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetString(rapidjson::StringRef(_openPortalFileName.c_str()));
	prototypeDoc.AddMember("E.OpenEntranceFileName", value);

	value.SetString(rapidjson::StringRef(_closePortalFileName.c_str()));
	prototypeDoc.AddMember("E.CloseEntranceFileName", value);

	value.SetString(rapidjson::StringRef(_nextScene.c_str()));
	prototypeDoc.AddMember("E.NextScene", value);

	value.SetInt(_progressCount);
	prototypeDoc.AddMember("E.ProgressCount", value);
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
}

void EntrancePortal::Update(double dt)
{
	if (dt < 0)
		return;

	if (!_init)
	{
		Init();
		_init = true;
		return;
	}

	if (!_clear)
	{
		if (!_playerScript)
		{
			std::string temp = "Player";
			_playerScript = MyLogicSystem.GetScriptList()[((LogicComponent*)(MyLinkFactory.GetLinkIDObject(999)->GetComponent(ComponentId::CT_Logic)))->GetScriptContianer()[ToScriptId(temp)]];
		}

		if (_KillCount >= _progressCount)
			OpenPortal();
	}
}

void EntrancePortal::OpenPortal()
{
	_clear = true;
	_graphicComponent->SetFileName(_openPortalFileName);
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
