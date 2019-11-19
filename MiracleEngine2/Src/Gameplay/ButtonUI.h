#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef BUTTON_UI_H
#define	BUTTON_UI_H

// create a enum for buttonType
enum class ButtonType {
	NONE = 0,
	PLAY = 1,
	PAUSE,
	QUIT,
	MENU,
	RESTART,
	CLOSE,
	OPEN,
};

class ButtonUI : public IScript
{
private:

public:
	int _buttonType;
//Constructor
	ButtonUI();
	void SerialiseComponent(Serialiser& document);


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetInt(_buttonType);
		prototypeDoc.AddMember("ButtonType", value);
		value.Clear();
	}

	void Inspect() override
	{

	}

// override these functions
	void OnMouseDown();
	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();

// InUpEx
	void Init();
	void Update();
	void Exit();

};

#endif
