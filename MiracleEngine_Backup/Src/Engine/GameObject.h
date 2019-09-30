#pragma once
#include "MathLib/SYMath.h"
#include <vector>
#include <string>
#include "Inputsystem/inputsystem.h"
#include "Tools/FileIO.h"

extern InputSystem* inputsystem;


enum GameObjectType {
	UNKOWN = 0,
	PLAYER,
	WALL,
	FLOOR,
	MISC,
};

struct GameObject
{
	int _id{ UNKOWN };

	GameObject(Vector3 pos = Vector3{ 0,0 }, Vector3 scale = Vector3{ 20,20 }, float angle = 0, const std::string& name = "zombie", bool isanimated = false) :
		_pos{pos}, _scale{scale}, _angle{angle}, _name{name}, _isAnimated{isanimated}
	{
	}
	virtual ~GameObject() = default;
	Vector3 _pos{ Vector3() };
	Vector3 _scale{ Vector3(1.f,1.f,1.f) };
	float _angle{ 0.0f };
	std::string _name;
	bool _isAnimated;

	virtual void Update() {
		std::cout << "A !" << std::endl;
	};
	virtual GameObject* Clone(Vector3 pos, Vector3 scale, float rotate)
	{
		return new GameObject();
	}
};

struct Wall : public GameObject {
	Wall()
	{
		_id = WALL;
	}
	~Wall()
	{
	}

	void Update() override
	{}

	Wall* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};

struct Floor : public GameObject {
	Floor()
	{
		_id = FLOOR;
	}
	~Floor()
	{
	}

	void Update() override
	{}

	Floor* Clone(Vector3 pos, Vector3 scale, float rotate) override;
};

struct Player : public GameObject {
	int _Health{ 0 };
	float _Speed{ 0.0f };
	std::vector<int> _WeaponListId;

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
		Vector3 move, scale;
		// based on key pressed, move player
		if (inputsystem->KeyDown(KEYB_UP))
			move.Y(_Speed);
		if (inputsystem->KeyDown(KEYB_DOWN))
			move.Y(-_Speed);
		if (inputsystem->KeyDown(KEYB_RIGHT))
			move.X(_Speed);
		if (inputsystem->KeyDown(KEYB_LEFT))
			move.X(-_Speed);
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
		_pos += move;
		_scale += scale;
	}
	
};

std::vector<GameObject*> FileRead_Level(const char* FileName);

extern std::vector<GameObject*> objList;
extern std::vector<GameObject*> objStressTestList;
extern std::map <std::string, GameObject*> objFab;