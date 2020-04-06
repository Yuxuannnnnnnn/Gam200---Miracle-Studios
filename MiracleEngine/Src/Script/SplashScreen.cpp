#include "PrecompiledHeaders.h"
#include "SplashScreen.h"

void SplashScreen::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("SS.splashObjectLinkId") && document["SS.splashObjectLinkId"].IsArray() &&
		document.HasMember("SS.splashObjectDuration") && document["SS.splashObjectDuration"].IsArray())	//Checks if the variable exists in .Json file
	{
		_totalSplash = document["SS.splashObjectLinkId"].Size();

		for (unsigned i = 0; i < _totalSplash; i++)
		{
			if (document["SS.splashObjectLinkId"][i].IsInt())
				_splashObjectLinkId.push_back(document["SS.splashObjectLinkId"][i].GetInt());

			if (document["SS.splashObjectDuration"][i].IsFloat())	//Checks if the variable exists in .Json file
				_splashObjectDuration.push_back(document["SS.splashObjectDuration"][i].GetFloat());

		}

	}
	
}

//function Not Needed for scripts
void SplashScreen::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
}

void SplashScreen::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{

}

void SplashScreen::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	
}

void SplashScreen::Inspect()
{
}

SplashScreen::SplashScreen() :  
	_timer{ 0.0 },
	_currSplash{0}
{
}

SplashScreen* SplashScreen::Clone()
{
	return new SplashScreen(*this);
}

void SplashScreen::Init()
{
	if (!_totalSplash)
		return;

	for (unsigned i = 0; i < _totalSplash; i++)
	{
		GameObject* temp = GetLinkObject(_splashObjectLinkId[i]);
		temp->SetEnable(false);
		_splashObject.push_back(temp);
	}

	_currSplash = 0;

	_splashObject[_currSplash]->SetEnable(true);
	_timer = _splashObjectDuration[_currSplash];
	++_currSplash;
}

void SplashScreen::LoadResource()
{

}

void SplashScreen::Update(double dt)
{
	if (_timer > 0)
		_timer -= dt;
	else
	{
		if (_currSplash < _totalSplash)
		{
			_splashObject[_currSplash - 1]->SetEnable(false);

			_splashObject[_currSplash]->SetEnable(true);
			_timer = _splashObjectDuration[_currSplash];
			++_currSplash;
		}
		else
			MyFactory.ChangeScene("MainMenu");
	}
}
