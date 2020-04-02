#include "PrecompiledHeaders.h"
#include "LoadingScreen.h"
#include "Script/Player.h"

void LoadingScreen::SerialiseComponent(Serialiser& document)
{
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

LoadingScreen::LoadingScreen()
{
}

LoadingScreen* LoadingScreen::Clone()
{
	return nullptr;
}

void LoadingScreen::Init()
{
}

void LoadingScreen::LoadResource()
{
}

void LoadingScreen::Update(double dt)
{
}

void LoadingScreen::StartLoading()
{
}
