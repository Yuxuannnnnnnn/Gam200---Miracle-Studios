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
	_loadingComplete{ false },
	_player{ nullptr },
	_continueButton{ nullptr }
{
}

LoadingScreen* LoadingScreen::Clone()
{
	return new LoadingScreen(*this);
}

void LoadingScreen::Init()
{
	if (_continueLinkId)
		_continueButton = GetLinkObject(_continueLinkId);

	if(_playerLinkId)
		_player = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(_playerLinkId), Logic), Player);
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
	if (_loadingComplete && _continueButton)
	{
		if (!_continueButton->GetEnable())
		{
			_input->_pause = true;
			_continueButton->SetEnable(true);

			GetSibilingComponentObject(Graphic)->SetFileName(_CompletedFileName);
		}
		else if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_SPACEBAR))
		{
			_input->_pause = false;
			_loadingComplete = false;
			_player->GetParentPtr()->SetEnable(true);
			GetParentPtr()->SetEnable(false);
			_continueButton->SetEnable(false);
		}
	}

}

void LoadingScreen::StartLoading()
{
	GetParentPtr()->SetEnable(true);

	if (_player)
		_player->GetParentPtr()->SetEnable(false);

	GetSibilingComponentObject(Graphic)->SetFileName(_LoadingFileName);

	_input->_pause = true;
	_loadingComplete = false;
}
