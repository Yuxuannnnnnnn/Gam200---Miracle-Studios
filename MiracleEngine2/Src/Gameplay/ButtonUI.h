#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

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
	// override these functions
	void OnMouseDown();
	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();

	// InUpEx
	void Init();
	void Update();
	void Exit();

	void SerialiseComponent(Serialiser& document);
};