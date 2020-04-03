#include "PrecompiledHeaders.h"
#include "LoadingScreen.h"
#include "Script/Player.h"

void LoadingScreen::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("L.FileName") && document["L.FileName"].IsString())
		_FileName = document["L.FileName"].GetString();

	if (document.HasMember("L.LoadingTextLinkId") && document["L.LoadingTextLinkId"].IsInt())
		_LoadingTextLinkId = document["L.LoadingTextLinkId"].GetInt();

	if (document.HasMember("L.playerExist") && document["L.playerExist"].IsBool())
		_playerExist = document["L.playerExist"].GetBool();

	if (document.HasMember("L.secondImage") && document["L.secondImage"].IsBool())
	{
		_secondImage = document["L.secondImage"].GetBool();
	
		if (_secondImage)
		{
			if (document.HasMember("L.FileName2") && document["L.FileName2"].IsString())
				_FileName2 = document["L.FileName2"].GetString();
		}
	}
	

	if (document.HasMember("L.panning") && document["L.panning"].IsBool())
	{
		_panning = document["L.panning"].GetBool();

		if (_panning)
		{
			if (document.HasMember("L.panningCameraLinkId") && document["L.panningCameraLinkId"].IsInt())
				_panningCameraLinkId = document["L.panningCameraLinkId"].GetInt();

			if (document.HasMember("L.startPosition") && document["L.startPosition"].IsArray())	//Checks if the variable exists in .Json file
			{
				if (document["L.startPosition"][0].IsFloat() && document["L.startPosition"][1].IsFloat())	//Check the array values
					_startPosition = Vector3{ document["L.startPosition"][0].GetFloat(), document["L.startPosition"][1].GetFloat(), 1 };

				if (document["L.startPosition"].Size() == 3)
					_startPosition.SetZ(document["L.startPosition"][2].GetFloat());
			}

			if (document.HasMember("L.endPosition") && document["L.endPosition"].IsArray())	//Checks if the variable exists in .Json file
			{
				if (document["L.endPosition"][0].IsFloat() && document["L.endPosition"][1].IsFloat())	//Check the array values
					_endPosition = Vector3{ document["L.endPosition"][0].GetFloat(), document["L.endPosition"][1].GetFloat(), 1 };

				if (document["L.endPosition"].Size() == 3)
					_endPosition.SetZ(document["L.endPosition"][2].GetFloat());
			}

			if (document.HasMember("L.startZoom") && document["L.startZoom"].IsFloat())	//Checks if the variable exists in .Json file
				_startZoom = (document["L.startZoom"].GetFloat());

			if (document.HasMember("L.endZoom") && document["L.endZoom"].IsFloat())	//Checks if the variable exists in .Json file
				_endZoom = (document["L.endZoom"].GetFloat());

			if (document.HasMember("L.panningSpeed") && document["L.panningSpeed"].IsFloat())	//Checks if the variable exists in .Json file
				_panningSpeed = (document["L.panningSpeed"].GetFloat());
		}
	}

	if (document.HasMember("L.loadingCompleted") && document["L.loadingCompleted"].IsBool())
		_loadingCompleted = document["L.loadingCompleted"].GetBool();


	if (document.HasMember("L.victoryTextLinkId") && document["L.victoryTextLinkId"].IsInt())
		_victoryTextLinkId = document["L.victoryTextLinkId"].GetInt();
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
	_FileName{},
	_LoadingTextLinkId{0},
	_cursorObj{nullptr},
	_playerExist{false},
	_player{nullptr},
	_secondImage{false},
	_FileName2{},
	_panning{false},
	_playerCamera{nullptr},
	_panningCameraLinkId{0},
	_camera{nullptr},
	_cameraTransform{ nullptr },
	_startPosition{},
	_endPosition{},
	_loadingCompleted{false},
	_victoryTextLinkId{0},
	_panningComleted{false},
	_nextScene{"Quit"}
{
}

LoadingScreen* LoadingScreen::Clone()
{
	return new LoadingScreen(*this);
}

void LoadingScreen::Init()
{
	GetSibilingComponentObject(UI)->SetFileName(_FileName);

	_cursorObj = GetLinkObject(9723);

	if(_playerExist)
		_player = GetScriptByLogicComponent(GetComponentObject(GetLinkObject(999), Logic), Player);

	if (_panning)
	{
		_camera = GetComponentObject(GetLinkObject(_panningCameraLinkId), Camera);
		_cameraTransform = GetComponentObject(GetLinkObject(_panningCameraLinkId), Transform);

		_moveSpeed = (_endPosition - _startPosition) * 0.01f;
		_zoomSpeed = (_endZoom - _startZoom) * 0.01f;
	}

	if (_loadingCompleted)
	{
		GetParentPtr()->SetEnable(true);
		_player->GetParentPtr()->SetEnable(false);
		_cursorObj->SetEnable(false);
		_input->_pause = true;

		if (_panning)
		{ 
			if(_playerExist)
				_playerCamera = GetComponentObject(GetLinkObject(999), Camera);
		
			_camera->SetMainCamera(true);
			_camera->_cameraZoom = _startZoom;
			_cameraTransform->SetPos(_startPosition);

			GetLinkObject(_LoadingTextLinkId)->SetEnable(false);

			if(_victoryTextLinkId)
				GetLinkObject(_victoryTextLinkId)->SetEnable(false);
		}
		else
			GetLinkObject(_LoadingTextLinkId)->SetEnable(true);
	}
	else
	{
		GetParentPtr()->SetEnable(false);
		GetLinkObject(_LoadingTextLinkId)->SetEnable(false);
	}

	_panningComleted = !_panning;
}

void LoadingScreen::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ _FileName, MyResourceSystem.GetTexture2DResourcePath(_FileName) });

	if(_secondImage)
		MyResourceManager.AddNewTexture2DResource({ _FileName2, MyResourceSystem.GetTexture2DResourcePath(_FileName2) });
#endif
}

void LoadingScreen::Update(double dt)
{
	if (_panning && !_panningComleted)
	{
		_cameraTransform->SetPos(_cameraTransform->GetPositionA() + _moveSpeed * dt * _panningSpeed);
		_camera->_cameraZoom += _zoomSpeed * dt * _panningSpeed;

		if (_camera->_cameraZoom > _endZoom)
		{
			_panningComleted = true;
			_cameraTransform->SetPos(_endPosition);
			_camera->_cameraZoom = _endZoom;

			if(_secondImage)
				GetSibilingComponentObject(UI)->SetFileName(_FileName2);

			GetLinkObject(_LoadingTextLinkId)->SetEnable(true);

			if (_victoryTextLinkId)
				GetLinkObject(_victoryTextLinkId)->SetEnable(true);
		}
	}

	if (_panningComleted)
	{
		if (_loadingCompleted)
		{
			if (_input->KeyDown(KeyCode::KEYB_SPACEBAR))
			{
				_input->_pause = false;

				GetParentPtr()->SetEnable(false);
				_player->GetParentPtr()->SetEnable(true);
				_cursorObj->SetEnable(true);

				GetLinkObject(_LoadingTextLinkId)->SetEnable(false);
			}
		}
		else
		{
			if (_victoryTextLinkId)
				if (_input->KeyDown(KeyCode::KEYB_SPACEBAR))
					MyFactory.ChangeScene(_nextScene);
				else
					MyFactory.ChangeScene(_nextScene);
		}
	}
}

void LoadingScreen::StartLoading(std::string nextScene)
{
	if (_loadingCompleted)
		return;

	_nextScene = nextScene;

	GetParentPtr()->SetEnable(true);
	_cursorObj->SetEnable(false);

	if (_playerExist)
		_player->GetParentPtr()->SetEnable(false);

	_input->_pause = true;


	if (_panning)
	{
		_camera->SetMainCamera(true);
		_camera->_cameraZoom = _startZoom;
		_cameraTransform->SetPos(_startPosition);

		GetLinkObject(_LoadingTextLinkId)->SetEnable(false);
	}
	else
		GetLinkObject(_LoadingTextLinkId)->SetEnable(true);
}
