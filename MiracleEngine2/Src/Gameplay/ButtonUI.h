#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

// create a enum for buttonType
enum class ButtonType {
	NONE = 0,
	PLAY,
	PAUSE,
	QUIT,
	MENU,
	RESTART,
};

class ButtonUI : public IScript
{
private:
	int _buttonType;
public:
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