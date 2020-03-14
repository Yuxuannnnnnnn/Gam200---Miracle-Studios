#include "PrecompiledHeaders.h"
#include "LoadingScreen.h"
#include "Script/Player.h"
#include "Script/EntrancePortal.h"

void LoadingScreen::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("L.LoadingFileName") && document["L.LoadingFileName"].IsString())
		_LoadingFileName = document["L.LoadingFileName"].GetString();

	if (document.HasMember("L.CompletedFileName") && document["L.CompletedFileName"].IsString())
		_CompletedFileName = document["L.CompletedFileName"].GetString();

	if (document.HasMember("L.PlayerLinkId") && document["L.PlayerLinkId"].IsInt())
		_playerLinkId = document["L.PlayerLinkId"].GetInt();

	if (document.HasMember("L.ContinueLinkId") && document["L.ContinueLinkId"].IsInt())
		_continueLinkId = document["L.ContinueLinkId"].GetInt();

	if (document.HasMember("L.LoadComplete") && document["L.LoadComplete"].IsBool())
		_loadingComplete = document["L.LoadComplete"].GetBool();

	if (document.HasMember("L.CursorLinkId") && document["L.CursorLinkId"].IsInt())
		_cursorLinkId = document["L.CursorLinkId"].GetInt();
}

void LoadingScreen::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void LoadingScreen::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void LoadingScreen::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
}

void LoadingScreen::Inspect()
{
}

LoadingScreen::LoadingScreen() :
	_LoadingFileName{},
	_CompletedFileName{},
	_playerLinkId{ 0 },
	_continueLinkId{ 0 },
	_cursorLinkId{0},
	_loadingComplete{ false },
	_player{ nullptr },
	_continueButton{ nullptr },
	_cursorObj{nullptr}
{
}

LoadingScreen* LoadingScreen::Clone()
{
	return new LoadingScreen(*this);
}

void LoadingScreen::Init()
{
	if (_loadingComplete)
	{
		_continueButton = GetLinkObject(_continueLinkId);
		_continueButton->SetEnable(true);
		_player = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(_playerLinkId), Logic), Player);
		_player->GetParentPtr()->SetEnable(false);
		GetSibilingComponentObject(UI)->SetFileName(_CompletedFileName);

		_input->_pause = true;
	}

	_cursorObj = GetLinkObject(_cursorLinkId);
	_cursorObj->SetEnable(false);
}

void LoadingScreen::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ _LoadingFileName, MyResourceSystem.GetTexture2DResourcePath(_LoadingFileName) });
	MyResourceManager.AddNewTexture2DResource({ _CompletedFileName, MyResourceSystem.GetTexture2DResourcePath(_CompletedFileName) });
#endif
}

void LoadingScreen::Update(double dt)
{
	if (_loadingComplete && _input->KeyDown(KeyCode::KEYB_SPACEBAR))
	{
		_input->_pause = false;
		_loadingComplete = false;
		_continueButton->SetEnable(false);
		_player->GetParentPtr()->SetEnable(true);
		GetParentPtr()->SetEnable(false);
		_cursorObj->SetEnable(true);

		GetSibilingComponentObject(UI)->SetFileName(_LoadingFileName);
	}
}

void LoadingScreen::StartLoading()
{
	if (_loadingComplete)
		_player->GetParentPtr()->SetEnable(false);

	GetParentPtr()->SetEnable(true);
	_cursorObj->SetEnable(false);
	_input->_pause = false;
}
