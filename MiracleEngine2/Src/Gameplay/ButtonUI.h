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
