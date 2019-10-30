#include "PrecompiledHeaders.h"
#include "Script.h"

namespace Script_1 {
	void Update()
	{
		std::cout << "SCRIPT - 1" << std::endl;
	}
}

namespace Script_2 {
	void Update(LogicComponent* parent)
	{
		std::cout << "SCRIPT - 2" << "\t :: \t";
		TransformComponent* temp = (TransformComponent*)parent->GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT);
		Vector3 tempVec = temp->GetPos();
		std::cout << tempVec._x << ",";		
		tempVec._x += 1;
		temp->GetPos() = tempVec;
		std::cout << tempVec._x;

		RigidBody2D* tempOne = (RigidBody2D*)parent->GetSibilingComponent((unsigned)TypeIdComponent::RIGIDBODYCOMPONENT);
		std::cout << "\t ~ " << tempOne->_angle;
		std::cout << std::endl;
	}
}

namespace Script_HealthMinus {
	void Update(int& health, int changeVal)
	{
		std::cout << "SCRIPT - HealthMinus" << std::endl;
	}
}

namespace Script_Input {

	//InputSystem keyboard;

	// functions to check key UpDownHold for chosen keys
	// GetKeyDown(AE_LEFT); GetKeyUp(ESCAPE); GetKeyHold(MB_RIGHT);
	void Logic_Input_MainMenu() // for menu input
	{
		// for MainMenu
	}
	void Logic_Input_Ingame(
		GameObjectFactory* factory, GameObject* player,
		InputSystem* input, Input_Style inputStyle) // for in game input
	{
		Vector3 moveResult; // for throwing resultant movement force to player
	 //OTHERS
		//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
		//	_InputStyle = INGAME_PAUSE_ESCAPE;
	// MOVEMENT		// in future need to do a speed multi OR leave it to phy to do it?
		if (input->KeyHold(KeyCode::KEYB_W))
			moveResult.Y(1.0f);
		if (input->KeyHold(KeyCode::KEYB_S))
			moveResult.Y(-1.0f);
		if (input->KeyHold(KeyCode::KEYB_D))
			moveResult.X(1.0f);
		if (input->KeyHold(KeyCode::KEYB_A))
			moveResult.X(-1.0f);
	// MOUSE
		if (input->KeyHold(KeyCode::MOUSE_LBUTTON))
		{
			Script_Shoot::Update(player, factory); // Shoot	
		}
		if (input->KeyHold(KeyCode::MOUSE_RBUTTON))
			(void)1; // Do something

	// give resultant to player
		//return moveResult;
	}
	void Logic_Input_IngamePause() // for ingame pause
	{
		// for InGame on Death, Upgrade, Levelup, EscapeKeyPress

		//if (keyboard.KeyDown(KEYB_ESCAPE)) // exit pause menu
		//	_InputStyle = INGAME;
		return;
	}

	void Update(
		GameObjectFactory* factory, GameObject* player,InputSystem* input)
	{
		std::cout << "SCRIPT - InputScript" << std::endl;

		switch (Input_Style::INGAME) // force INGAME style only
		{
		case Input_Style::OFF:
			return;
		case Input_Style::MAIN_MENU:
			Logic_Input_MainMenu();
			return;
		case Input_Style::INGAME:
			Logic_Input_Ingame(factory, player, input, Input_Style::INGAME);
			return;
		case Input_Style::INGAME_PAUSE_ESCAPE:
			Logic_Input_IngamePause();
			return;
		default:
			return;
		}
	}
}

namespace Script_Shoot {
	void Update(GameObject* obj, GameObjectFactory* factory) // obj can be PLAYER or ENEMEY
	{
		std::cout << "SCRIPT - Shoot" << std::endl;
		// get obj.transform
		Vector3 pos =
			((TransformComponent*)obj->GetComponent(TypeIdComponent::TRANSFORMCOMPONENT))->GetPos();
		float rot =
			((TransformComponent*)obj->GetComponent(TypeIdComponent::TRANSFORMCOMPONENT))->GetRotate();
		// spawn bullet
		GameObject* temp = nullptr;
		factory->CloneGameObject(TypeIdGO::BULLET);

		// move bullet in direction of obj

	}
}
