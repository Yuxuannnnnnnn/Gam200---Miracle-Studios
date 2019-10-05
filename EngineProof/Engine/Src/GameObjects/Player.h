#pragma once

#include "MathLib/SYMath.h"
#include <vector>
#include <string>
#include "Inputsystem/inputsystem.h"
#include "Tools/FileIO.h"
#include "PhysicSystem/RigidBody2D.h"
#include "..\GameObjects\GameObject.h"
#include "PhysicSystem/BoxCollider2D.h"


struct Player : public GameObject {

	int _Health{ 0 };
	float _Speed{ 0.0f };
	std::vector<int> _WeaponListId;

	RigidBody2D* _body{ nullptr };
	BoxCollider2D* _collider{ nullptr };

	bool _keypressed{false};

	Player()
	{
		_id = PLAYER;
	}
	~Player()
	{
	}

	virtual void Update()
	{
		Movement();
	}
	Player* Clone(Vector3 pos, Vector3 scale, float rotate) override;


	void Picking(Vector3 point)
	{
		if (inputsystem->KeyDown(MOUSE_LBUTTON) )
		{
			if (!_keypressed)
			{
				if (_collider->TestBoxVsPoint(point))
					std::cout << "player got Picked" << point << std::endl;
			}

			_keypressed = true;
		}
		else
			_keypressed = false;
	}

	void Serialize()
	{
		std::cout << "FileRead_PlayerInfo -----------------" << std::endl;
		rapidjson::Document d;
		char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/player.json");
		std::cout << iBuffer << std::endl;
		ASSERT(iBuffer != nullptr);
		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
		// get values from the Document;

		rapidjson::Value& s = d["Health"];
		JsonDynamicStore(_Health, s);

		s = d["Speed"];
		JsonDynamicStore(_Speed, s);

		s = d["Weapons"];
		JsonDynamicStore(_WeaponListId, s);

		s = d["Position"];
		JsonDynamicStore(_pos, s);

		s = d["Scale"];
		JsonDynamicStore(_scale, s);

		s = d["Rotate"];
		JsonDynamicStore(_angle, s);

		std::cout << "-------------------------------------" << std::endl;

		delete[] iBuffer;
	}

	void Movement() // will move to LogicComponent->Player
	{
		Vector3 scale;
		// based on key pressed, move player
		if (inputsystem->KeyDown(KEYB_UP))
		{
			_body->_appliedForce = Vector3(0.f, 30.f * _Speed,0.f);
		}
		if (inputsystem->KeyDown(KEYB_DOWN))
		{
			_body->_appliedForce = Vector3(0.f, -30.f * _Speed, 0.f);
		}
		if (inputsystem->KeyDown(KEYB_RIGHT))
		{
			_body->_appliedForce = Vector3(30.f * _Speed,0.f, 0.f);
		}
		if (inputsystem->KeyDown(KEYB_LEFT))
		{
			_body->_appliedForce = Vector3(-30.f * _Speed, 0.f, 0.f);
		}
		if (inputsystem->KeyDown(KEYB_U))
			_angle += 0.1f;
		if (inputsystem->KeyDown(KEYB_O))
			_angle -= 0.1f;
		if (inputsystem->KeyDown(KEYB_I))
			scale.Y(1);
		if (inputsystem->KeyDown(KEYB_K))
			scale.Y(-1);
		if (inputsystem->KeyDown(KEYB_J))
			scale.X(1);
		if (inputsystem->KeyDown(KEYB_L))
			scale.X(-1);
		_scale += scale;
	}

};