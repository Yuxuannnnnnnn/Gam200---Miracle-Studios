#include "PrecompiledHeaders.h"
#include "Script.h"

namespace Script_1 {
	void Update()
	{
		//std::cout << "SCRIPT - 1" << std::endl;
	}
}

namespace Script_2 {
	void Update(LogicComponent* parent)
	{
		//std::cout << "SCRIPT - 2" << "\t :: \t";
		//TransformComponent* temp = (TransformComponent*)parent->GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT);
		//Vector3 tempVec = temp->GetPos();
		//std::cout << tempVec._x << ",";		
		//tempVec._x += 1;
		//temp->GetPos() = tempVec;
		//std::cout << tempVec._x;

		//RigidBody2D* tempOne = (RigidBody2D*)parent->GetSibilingComponent((unsigned)TypeIdComponent::RIGIDBODYCOMPONENT);
		//std::cout << "\t ~ " << tempOne->_angle;
		//std::cout << std::endl;
	}
}

namespace Script_HealthMinus {
	void Update(int& health, int changeVal)
	{
		//std::cout << "SCRIPT - HealthMinus" << std::endl;
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
	// MOVEMENT
		// get spd
		float spd = (float)((LogicComponent*)(player->GetComponent(TypeIdComponent::LOGICCOMPONENT)))->GetSpeed();
		//spd *= 30.f;
		if (input->KeyHold(KeyCode::KEYB_W))
			moveResult.Y(spd);
		if (input->KeyHold(KeyCode::KEYB_S))
			moveResult.Y(-spd);
		if (input->KeyHold(KeyCode::KEYB_D))
			moveResult.X(spd);
		if (input->KeyHold(KeyCode::KEYB_A))
			moveResult.X(-spd);
		// add force
			// ((RigidBody2D*)(player->GetComponent(TypeIdComponent::RIGIDBODYCOMPONENT)))->AddForce(moveResult);
		// move by Transform eddit (WRONG WAY, waiting for SY to get his RBody up)
		{
			Vector3 a = ((TransformComponent*)(player->GetComponent(TypeIdComponent::TRANSFORMCOMPONENT)))->GetPos();
			a += moveResult;
			((TransformComponent*)(player->GetComponent(TypeIdComponent::TRANSFORMCOMPONENT)))->GetPos() = a;
		}
	// MOUSE
		if (input->KeyDown(KeyCode::MOUSE_LBUTTON))
		{
			Script_Shoot::Update(player, factory); // Shoot	
		}
		if (input->KeyDown(KeyCode::MOUSE_RBUTTON))
		{
			//delete all Bullet in 'factory'
				//for (auto const& x : factory->getObjectlist())
				//	if (x.second->Get_typeId() == (unsigned)TypeIdGO::BULLET)
				//		factory->DeleteGameObjectID(x.first);
			std::unordered_map < size_t, GameObject* > temp = factory->getObjectlist();
			std::unordered_map < size_t, GameObject* >::iterator itr = temp.begin();
			std::vector <size_t> toDelete;
			while (itr != temp.end())
			{
				if (itr->second->Get_typeId() == (unsigned)TypeIdGO::BULLET)
					//delete temp[itr->first];
					//temp.erase(itr->first);
					//itr = temp.begin();

					//factory->DeleteGameObjectID(itr->first);

					toDelete.push_back(itr->first);
				++itr;
			}

			for (auto const& x : toDelete)
				factory->DeleteGameObjectID(x);

			temp = factory->getObjectlist();
			int a = 0;
		}

		//// get mouse position and rotate player to face mouse
		//_aimVector = { (float)MousePos.x - SCREEN_WIDTH_HALF,
		//					-((float)MousePos.y - SCREEN_HEIGHT_HALF) };
		//
		//
		//AEMtx33 final, matri, scale, rot, trans;
		//// calc rot
		//CRMath_Vector compareVec = { 0, 1 };
		//float dot = _aimVector.x * compareVec.x + _aimVector.y * compareVec.y;
		//float det = _aimVector.x * compareVec.y - _aimVector.y * compareVec.x;
		//float angle = atan2(det, dot);
		//// Compute the scaling matrix
		//AEMtx33Scale(&scale, 1.0f, 1.0f);
		//// Compute the rotation matrix
		//AEMtx33Rot(&rot, -angle);
		//// Compute the translation matrix
		//AEMtx33Trans(&trans, position.x, position.y);
		//AEMtx33Concat(&matri, &trans, &rot);
		//AEMtx33Concat(&final, &matri, &scale);
		//AEGfxSetTransform(final.m);
		//
		//
		//_gunFirePrev = _gunFire;
		//_gunFire = _gunNumber;
		//if (_gunNumber == BULLET_SHOT)
		//{
		//	if (_gunFirePrev == BULLET_SHOT)
		//	{
		//		if (_gunStreak < PLAYER_GUNSTREAK_MAXSTACKS)
		//			++_gunStreak;
		//	}
		//	for (int i = 0; i <= _gunStreak; ++i)
		//	{
		//		objectBulletList->push_back(
		//			ObjectFactory_createBullet(objectRepo, position, RotateVector(_aimVector, (float)i), pCollision, _gunNumber, relativeVelocity)
		//		);
		//		objectBulletList->push_back(
		//			ObjectFactory_createBullet(objectRepo, position, RotateVector(_aimVector, (float)-i), pCollision, _gunNumber, relativeVelocity)
		//		);
		//	}

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
	void Update(GameObject* obj, GameObjectFactory* factory)
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
		// set bullet position as same as 'parent' obj

		// move bullet in direction of obj
		
	}
}
