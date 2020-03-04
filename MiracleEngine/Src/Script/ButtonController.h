#pragma once
#include "GameObject/Components/Logic/IScript2.h"

enum class SceneTag {
	NONE = 0,
	MAINMENU,
	POPUPSCENE,

	TOTAL_TAG
};

inline const char* ToString(SceneTag type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case SceneTag::NONE:			return "NONE";
	case SceneTag::MAINMENU:			return "MAIN MENU";

	default:      return "[Unknown SceneTag]";
	}
}

class ButtonController : public IScript2
{
private:
	int _currScene;

	IScript2* _pauseMenu;
public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect();

	ButtonController();
	ButtonController* Clone();

	void Init();
	void Update(double dt);
};

